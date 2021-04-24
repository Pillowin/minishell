/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:51:00 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 00:08:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	// TODO: remove all fd in builtin
*/

void	redir_init(t_token *token, int (*fildes)[4])
{
	redir_destroy(fildes);	// TODO: check ?

	if (token->data[0][0] == '>')
	{
		(*fildes)[REAL_OUT] = dup(STDOUT_FILENO);
		if ((*fildes)[REAL_OUT] == -1)
		{
			// TODO: cannot dup
			printf("err : %s\n", strerror(errno));
			return ;
		}
		if (token->data[0][1] == '>')
			(*fildes)[OUT] = open(token->data[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			(*fildes)[OUT] = open(token->data[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (dup2((*fildes)[OUT], STDOUT_FILENO) == -1)
		{
			// TODO: cannot dup2
			printf("err : %s\n", strerror(errno));
			return ;
		}
	}

	if (token->data[0][0] == '<')
	{
		(*fildes)[REAL_IN] = dup(STDIN_FILENO);
		if ((*fildes)[REAL_IN] == -1)
		{
			// TODO: cannot dup
			printf("err : %s\n", strerror(errno));
			return ;
		}
		(*fildes)[IN] = open(token->data[1], O_RDONLY);
		if (dup2((*fildes)[IN], STDIN_FILENO) == -1)
		{
			// TODO: cannot dup2
			printf("err : %s\n", strerror(errno));
			return ;
		}
	}


	if ((*fildes)[OUT] == -1 || (*fildes)[IN] == -1)
	{
		// TODO: cannot open
		printf("err : %s\n", strerror(errno));
		return ;
	}
}

/*
**
*/

void	redir_destroy(int (*fildes)[4])
{
	if ((*fildes)[REAL_IN] != -1)
	{
		if (dup2((*fildes)[REAL_IN], STDIN_FILENO) == -1)
		{
			// TODO: cannot redup
			printf("err : %s\n", strerror(errno));
			return ;
		}
		(*fildes)[REAL_IN] = -1;
	}
	if ((*fildes)[IN] != STDIN_FILENO)
	{
		if (close((*fildes)[IN]) == -1)
		{
			// TODO: cannot close
			return ;
		}
		(*fildes)[IN] = STDIN_FILENO;
	}

	if ((*fildes)[REAL_OUT] != -1)
	{
		if (dup2((*fildes)[REAL_OUT], STDOUT_FILENO) == -1)
		{
			// TODO: cannot redup
			printf("err : %s\n", strerror(errno));
			return ;
		}
		(*fildes)[REAL_OUT] = -1;
	}
	if ((*fildes)[OUT] != STDOUT_FILENO)
	{
		if (close((*fildes)[OUT]) == -1)
		{
			// TODO: cannot close
			return ;
		}
		(*fildes)[OUT] = STDOUT_FILENO;
	}
}
