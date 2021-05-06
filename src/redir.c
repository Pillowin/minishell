/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:51:00 by agautier          #+#    #+#             */
/*   Updated: 2021/05/03 17:05:40 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	// TODO: remove all fd in builtin
*/

char	redir_init(t_token *token, int (*redirs)[4])
{
	int	type;

	type = IN;
	if (token->data[0][0] == '>')
		type = OUT;
	if (!redir_destroy(type, redirs))	// TODO: check ?
		return (FAILURE);
	(*redirs)[REAL + type] = dup(type);
	if ((*redirs)[REAL + type] == -1)
		return (FAILURE);
	if (token->data[0][0] == '<')
		(*redirs)[type] = open(token->data[1], O_RDONLY);
	else if (token->data[0][1] == '>')
		(*redirs)[type] = open(token->data[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		(*redirs)[type] = open(token->data[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((*redirs)[type] == -1)
		return (FAILURE);
	if (dup2((*redirs)[type], type) == -1)
		return (FAILURE);
	return (SUCCESS);
}

/*
**	
*/

char	redir_destroy(int type, int (*redirs)[4])
{
	if ((*redirs)[REAL + type] != -1)
	{
		if (dup2((*redirs)[REAL + type], type) == -1)
			return (FAILURE);
		(*redirs)[REAL + type] = -1;
	}
	if ((*redirs)[type] != type)
	{
		if (close((*redirs)[type]) == -1)
			return (FAILURE);
		(*redirs)[type] = type;
	}
	return (SUCCESS);
}
