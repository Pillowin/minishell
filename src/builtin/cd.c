/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:13:43 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 22:39:335 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

static int	cmp(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}

/*
**
*/
unsigned char	builtin_cd(t_token *cmd, t_list **env, t_err *err)
{
	t_list	*lst;
	char	*oldpwd;
	char	*pwd;

	if (!(cmd->data[1]))	// cd sans arg
	{
		lst = ft_list_find(*env, "HOME", &cmp);
		if (lst)
		{
			if (!(((t_var *)lst->data)->value))
				return (FAILURE);
			if (chdir((((t_var *)lst->data)->value)) == -1)
			{
				print_err_msg(err->cmd_name, (((t_var *)lst->data)->value), strerror(errno), err->gc);
				return (SUCCESS);
			}
			oldpwd = getcwd(NULL, 0);
			if (!oldpwd)
				return ((long)error(err, FATAL, NULL, NULL));
			gc_register(err->gc, oldpwd);
			if (!update_env(env, "OLDPWD", oldpwd, err->gc))
				return ((long)error(err, FATAL, NULL, NULL));
			pwd = ft_strdup((((t_var *)lst->data)->value));
			if (!pwd)
				return ((long)error(err, FATAL, NULL, NULL));
			gc_register(err->gc, pwd);
			if (!update_env(env, "PWD", pwd, err->gc))
				return ((long)error(err, FATAL, NULL, NULL));
			return (SUCCESS);
		}
		return ((long)error(err, HOME_NOT_SET, NULL, NULL));
	}
	else if (cmd->data[2])	// trop d'arg
		return ((long)error(err, TOO_MANY_ARG, NULL, NULL));
	else if (*(cmd->data[1]) == '-')	// cd -
	{
		// pwd = on veut recuperer PWD
		pwd = getcwd(NULL, 0);	// TODO: verif
		gc_register(err->gc, pwd);
		// oldpwd = on veut recuperer OLDPWD
		lst = ft_list_find(*env, "OLDPWD", &cmp);
		if (!lst)
			return ((long)error(err, OLDPWD_NOT_SET, NULL, NULL));
		oldpwd = ft_strdup(((t_var *)lst->data)->value);
		if (!oldpwd)
			return ((long)error(err, FATAL, NULL, NULL));
		gc_register(err->gc, oldpwd);
		// se déplacer dans oldpwd
		if (chdir(oldpwd) == -1)
		{
			print_err_msg(err->cmd_name, oldpwd, strerror(errno), err->gc);
			return (SUCCESS);
		}
		// update PWD
		if (!update_env(env, "PWD", oldpwd, err->gc))
			return ((long)error(err, FATAL, NULL, NULL));
		// update OLDPWD
		if (!update_env(env, "OLDPWD", pwd, err->gc))
			return ((long)error(err, FATAL, NULL, NULL));
	}
	else	// cas standard
	{
		// oldpwd = on veut recuperer OLDPWD
		oldpwd = getcwd(NULL, 0);	// TODO: verif
		gc_register(err->gc, oldpwd);
		if (chdir(cmd->data[1]) == -1)
		{
			print_err_msg(err->cmd_name, cmd->data[1], strerror(errno), err->gc);
			return (SUCCESS);
		}
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return ((long)error(err, FATAL, NULL, NULL));
		gc_register(err->gc, pwd);
		if (!update_env(env, "PWD", pwd, err->gc))
			return ((long)error(err, FATAL, NULL, NULL));
		if (!update_env(env, "OLDPWD", oldpwd, err->gc))
			return ((long)error(err, FATAL, NULL, NULL));
	}
	return (SUCCESS);
}
