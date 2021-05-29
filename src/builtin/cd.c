/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:13:43 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 14:11:1 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Update both PWD and OLDPWD var in environment.
*/
char	update_pwd_oldpwd(char *pwd, char *oldpwd, t_list **env, t_list **gc)
{
	char	*str;
	t_var	*var;

	str = gc_strjoin("PWD=", pwd, gc);
	if (!str)
		return (FAILURE);
	var = var_init(str, gc);
	if (!var)
		return (FAILURE);
	env_update(env, var, gc);
	gc_free(gc, (void **)&str);
	str = gc_strjoin("OLDPWD=", oldpwd, gc);
	if (!str)
		return (FAILURE);
	var = var_init(str, gc);
	if (!var)
		return (FAILURE);
	env_update(env, var, gc);
	gc_free(gc, (void **)&str);
	gc_free(gc, (void **)&pwd);
	gc_free(gc, (void **)&oldpwd);
	return (SUCCESS);
}

/*
**	cd
**	Change current working directory to $HOME.
*/
char	cd_no_arg(t_list **env, t_err *err)
{
	t_list	*lst;
	char	*oldpwd;
	char	*pwd;

	lst = ft_list_find(*env, "HOME", &cmp_var_name);
	if (!lst)
		return ((long)error(err, HOME_NOT_SET, NULL, NULL));
	if (!(((t_var *)lst->data)->value))
		return (FAILURE);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, oldpwd);
	if (chdir((((t_var *)lst->data)->value)) == -1)
	{
		perr_msg(err->cmd_name, (((t_var *)lst->data)->value),
			strerror(errno), err->gc);
		g_exit_status = EXIT_FAILURE;
		return ((long)error(err, NONE, NULL, NULL));
	}
	pwd = gc_strdup((((t_var *)lst->data)->value), err->gc);
	if (!pwd || !update_pwd_oldpwd(pwd, oldpwd, env, err->gc))
		return ((long)error(err, FATAL, NULL, NULL));
	return (SUCCESS);
}

/*
**	cd -
**	Change current working directory to $OLDPWD.
*/
char	cd_oldpwd(t_list **env, t_err *err)
{
	t_list	*lst;
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, pwd);
	lst = ft_list_find(*env, "OLDPWD", &cmp_var_name);
	if (!lst)
		return ((long)error(err, OLDPWD_NOT_SET, NULL, NULL));
	oldpwd = ft_strdup(((t_var *)lst->data)->value);
	if (!oldpwd)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, oldpwd);
	if (chdir(oldpwd) == -1)
	{
		perr_msg(err->cmd_name, oldpwd, strerror(errno), err->gc);
		g_exit_status = EXIT_FAILURE;
		return ((long)error(err, NONE, NULL, NULL));
	}
	if (!update_pwd_oldpwd(oldpwd, pwd, env, err->gc))
		return ((long)error(err, FATAL, NULL, NULL));
	return (SUCCESS);
}

/*
**	cd xxx
**	Change current working directory to xxx.
*/
char	cd(t_token *cmd, t_list **env, t_err *err)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, oldpwd);
	if (chdir(cmd->data[1]) == -1)
	{
		perr_msg(err->cmd_name, cmd->data[1], strerror(errno), err->gc);
		g_exit_status = EXIT_FAILURE;
		return ((long)error(err, NONE, NULL, NULL));
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, pwd);
	if (!update_pwd_oldpwd(pwd, oldpwd, env, err->gc))
		return ((long)error(err, FATAL, NULL, NULL));
	return (SUCCESS);
}

/*
**	Change current working directory.
*/
char	builtin_cd(t_token *cmd, t_list **env, t_err *err)
{
	if (!(cmd->data[1]))
		return (cd_no_arg(env, err));
	else if (cmd->data[2])
		return ((long)error(err, TOO_MANY_ARG, NULL, NULL));
	else if (*(cmd->data[1]) == '-')
		return (cd_oldpwd(env, err));
	return (cd(cmd, env, err));
}
