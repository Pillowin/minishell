/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:51:00 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 15:57:37 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	// TODO: remove all fd in builtin
*/

void	redir_init(t_token *token, int (*fildes)[4])
{
	int	type;

	type = IN;
	if (token->data[0][0] == '>')
		type = OUT;
	redir_destroy(type, fildes);	// TODO: check ?
	(*fildes)[REAL + type] = dup(type);
	if ((*fildes)[REAL + type] == -1)
	{
		// TODO: cannot dup
		printf("err : %s\n", strerror(errno));
		return ;
	}
	if (token->data[0][0] == '<')
		(*fildes)[type] = open(token->data[1], O_RDONLY);
	else if (token->data[0][1] == '>')
		(*fildes)[type] = open(token->data[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		(*fildes)[type] = open(token->data[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((*fildes)[type] == -1)
	{
		// TODO: cannot open
		printf("err : %s\n", strerror(errno));
		return ;
	}
	if (dup2((*fildes)[type], type) == -1)
	{
		// TODO: cannot dup2
		printf("err : %s\n", strerror(errno));
		return ;
	}
}

/*
**	
*/

void	redir_destroy(int type, int (*fildes)[4])
{
	if ((*fildes)[REAL + type] != -1)
	{
		if (dup2((*fildes)[REAL + type], type) == -1)
		{
			// TODO: cannot redup
			printf("err : %s\n", strerror(errno));
			return ;
		}
		(*fildes)[REAL + type] = -1;
	}
	if ((*fildes)[type] != type)
	{
		if (close((*fildes)[type]) == -1)
		{
			// TODO: cannot close
			printf("err : %s\n", strerror(errno));
			return ;
		}
		(*fildes)[type] = type;
	}
}
