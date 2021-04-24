/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:51:00 by agautier          #+#    #+#             */
/*   Updated: 2021/04/24 21:55:30 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/

void	redir_init(t_token *token, int *fd)
{
	redir_destroy(fd);	// TODO: check ?
	if (token->data[0][1] == '>')
		*fd = open(token->data[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (token->data[0][1] == '\0')
		*fd = open(token->data[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*fd == -1)
	{
		// TODO: cannot open
		printf("err : %s\n", strerror(errno));
		return ;
	}
}

/*
**
*/

void	redir_destroy(int *fd)
{
	if (*fd != STDOUT_FILENO)
	{
		if (close(*fd) == -1)
		{
			// TODO: cannot close
			return ;
		}
	}
	*fd = STDOUT_FILENO;
}
