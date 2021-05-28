/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:52:54 by agautier          #+#    #+#             */
/*   Updated: 2021/05/28 18:57:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check for errors before returning environment as an array.
*/
static char	**check_errors(char *path, t_list **env, t_err *err)
{
	char		**envp;
	struct stat	buf;

	if (stat(path, &buf) != 0)
		return (error(err, CMD_NOT_FOUND, NULL, NULL));
	if (buf.st_mode & S_IFDIR)
		return (error(err, IS_A_DIR, NULL, NULL));
	else if (!(buf.st_mode & S_IXUSR))
		return (error(err, CMD_PERM, NULL, NULL));
	envp = env_to_tab(*env, err->gc);
	if (!envp)
		return (error(err, FATAL, NULL, NULL));
	return (envp);
}

/*
**	Execute with execve a command.
*/
char	binary_exec(t_token *token, char *path, t_fd_env_err *fee)
{
	char	**envp;
	int		status;
	t_pid	pid;

	envp = check_errors(path, fee->env, fee->err);
	if (!envp)
		return (FAILURE);
	if (!(fee->fd->is_forked) || !(fee->fd->is_child))
	{
		pid = fork();
		if (pid == -1)
			return ((long)error(fee->err, FATAL, NULL, NULL));
		else if (!pid)
			if (execve(path, token->data, envp) == -1)
				return ((long)error(fee->err, FATAL, NULL, NULL));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			g_exit_status = WEXITSTATUS(status);
			return (SUCCESS);
		}
		return (SUCCESS);
	}
	execve(path, token->data, envp);
	return (FAILURE);
}
