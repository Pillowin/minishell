/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:48:33 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 16:32:12 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
static char	pipe_init_standard(t_fd *fd)
{
	if (!(fd->pid))
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
	if (!pipe_init_standard(fd))
		return (FAILURE);
	return (SUCCESS);
}

/*
**
*/
static char	pipe_destroy_out(t_fd *fd)
{
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
	if (!pipe_destroy_out(fd))
		return (FAILURE);
	fd->is_child = 0;
	fd->is_forked = 0;
	return (SUCCESS);
}
