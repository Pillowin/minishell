/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:48:33 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/03 19:36:46 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!(fd->pid))	// MIOCHE (cmd gauche)
	{
		// fprintf(stderr, "enfant 1\n");
		if (dup2(fd->pipes[OUT], STDOUT_FILENO) == -1)//STDOUT n'est plus STANDARD
			return (FAILURE);
		// fprintf(stderr, "enfant 2\n");
		fd->is_child = 1;
		if (close(fd->pipes[IN]) == -1)
			return (FAILURE);
		fd->pipes[IN] = STDIN_FILENO;//STDIN devient STANDARD
	}
	else	// PAPA (droite)
	{
		// fprintf(stderr, "papa 1 \n");
		if (dup2(fd->pipes[IN], STDIN_FILENO) == -1) //STDIN n'est plus STANDARD
			return (FAILURE);
		// fprintf(stderr, "papa 2\n");
		fd->is_child = 0;
		if (close(fd->pipes[OUT]) == -1)
			return (FAILURE);
		fd->pipes[OUT] = STDOUT_FILENO;//STDOUT devient STANDARD
	}
	// fprintf(stderr, "enfant 3\n\n");
	// fprintf(stderr, "papa 3\n\n");

	return (SUCCESS);
}

char	pipe_destroy(t_fd *fd)
{
	waitpid(-1, NULL, 0);
	if (fd->pipes[IN] != STDIN_FILENO) // Si IN n'est pas standard
	{
		if (close(fd->pipes[IN]) == -1)
			return (FAILURE);
		fd->pipes[IN] = STDIN_FILENO;//STDIN devient STANDARD
	}
	if (fd->pipes[REAL_IN] != -1)
	{
		if (dup2(fd->pipes[REAL_IN], STDIN_FILENO) == -1)
			return (FAILURE);
		fd->pipes[REAL_IN] = -1;
	}
	if (fd->pipes[OUT] != STDOUT_FILENO) // Si OUT n'est pas standard
	{
		if (close(fd->pipes[OUT]) == -1)
			return (FAILURE);
		fd->pipes[OUT] = STDOUT_FILENO;//TODO:STDOUT devient STANDARD
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
