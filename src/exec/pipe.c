/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:48:33 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 21:43:34 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
char	pipe_init(t_fd *fd)
{
	if (pipe(fd->pipes) == -1)
		return (FAILURE);
	if (fd->pipes[REAL_IN] == -1)
	{
		fd->pipes[REAL_IN] = dup(STDIN_FILENO);
		if (fd->pipes[REAL_IN] == -1)
			return (FAILURE);
	}
	if (fd->pipes[REAL_OUT] == -1)
	{
		fd->pipes[REAL_OUT] = dup(STDOUT_FILENO);
		if (fd->pipes[REAL_OUT] == -1)
			return (FAILURE);
	}
	fd->is_forked = 1;
	fd->pid = fork();
	if (fd->pid == -1)
		return (FAILURE);
	else if (!(fd->pid))
	{
		if (dup2(fd->pipes[OUT], STDOUT_FILENO) == -1)
			return (FAILURE);
		fd->is_child = 1;
		if (close(fd->pipes[IN]) == -1)
			return (FAILURE);
		fd->pipes[IN] = STDIN_FILENO;
	}
	else
	{
		if (dup2(fd->pipes[IN], STDIN_FILENO) == -1)
			return (FAILURE);
		fd->is_child = 0;
		if (close(fd->pipes[OUT]) == -1)
			return (FAILURE);
		fd->pipes[OUT] = STDOUT_FILENO;
	}
	return (SUCCESS);
}

/*
**
*/
char	pipe_destroy(t_fd *fd)
{
	waitpid(-1, NULL, 0);
	if (fd->pipes[IN] != STDIN_FILENO)
	{
		if (close(fd->pipes[IN]) == -1)
			return (FAILURE);
		fd->pipes[IN] = STDIN_FILENO;
	}
	if (fd->pipes[REAL_IN] != -1)
	{
		if (dup2(fd->pipes[REAL_IN], STDIN_FILENO) == -1)
			return (FAILURE);
		fd->pipes[REAL_IN] = -1;
	}
	if (fd->pipes[OUT] != STDOUT_FILENO)
	{
		if (close(fd->pipes[OUT]) == -1)
			return (FAILURE);
		fd->pipes[OUT] = STDOUT_FILENO;
	}
	if (fd->pipes[REAL_OUT] != -1)
	{
		if (dup2(fd->pipes[REAL_OUT], STDOUT_FILENO) == -1)
			return (FAILURE);
		fd->pipes[REAL_OUT] = -1;
	}
	fd->is_child = 0;
	fd->is_forked = 0;
	return (SUCCESS);
}
