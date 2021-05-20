/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:56:52 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 14:56:53 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	If builtin execution returns an error, exit fork.
*/
static char	exec_error(t_fd *fd, t_err *err)
{
	if (fd->is_child)
	{
		gc_clean(err->gc);
		exit(g_exit_status & 0x00FF);
	}
	return (FAILURE);
}

/*
**	If builtin execution returns a success, close pipe and exit fork.
*/
static char	exec_success(t_fd *fd, t_err *err)
{
	if (fd->is_child)
	{
		if (close(fd->pipes[OUT]) == -1)
			return ((long)error(err, FATAL, NULL, NULL));
		fd->pipes[OUT] = STDOUT_FILENO;
		gc_clean(err->gc);
		exit(g_exit_status & 0x00FF);
	}
	return (DONE);
}

/*
**	Init builtins pointer function table.
*/
static void	init_builtins(char (*builtins[7])(t_token *, t_list **, t_err *))
{
	builtins[0] = &builtin_echo;
	builtins[1] = &builtin_cd;
	builtins[2] = &builtin_pwd;
	builtins[3] = &builtin_export;
	builtins[4] = &builtin_unset;
	builtins[5] = &builtin_env;
	builtins[6] = &builtin_exit;
}

/*
**	If command is a builtin, execute it and return DONE.
**	Else return SUCCESS.
*/
char	is_builtin(t_token *token, t_fd *fd, t_list **env, t_err *err)
{
	unsigned int	i;
	const char		*builtin_names[7] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	char			(*builtins[7])(t_token *, t_list **, t_err *);

	init_builtins(builtins);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(token->data[0], (char *)builtin_names[i]))
		{
			if (!builtins[i](token, env, err))
				return (exec_error(fd, err));
			return (exec_success(fd, err));
		}
		i++;
	}
	return (SUCCESS);
}
