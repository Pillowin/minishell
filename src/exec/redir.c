/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:51:00 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 20:54:18 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	// TODO: remove all fd in builtin
*/

char	redir_init(t_token *token, int (*redirs)[4], t_err *err)
{
	int	type;

	type = IN;
	if (token->data[0][0] == '>')
		type = OUT;
	if (!redir_destroy(type, redirs, err))
		return (FAILURE);
	(*redirs)[REAL + type] = dup(type);
	if ((*redirs)[REAL + type] == -1)
		return ((long)error(err, FATAL, NULL, NULL));
	if (token->data[0][0] == '<')
		(*redirs)[type] = open(token->data[1], O_RDONLY);
	else if (token->data[0][1] == '>')
		(*redirs)[type] = open(token->data[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		(*redirs)[type] = open(token->data[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((*redirs)[type] == -1)
	{
		err->cmd_name = ft_strdup(token->data[1]);
		if (!(err->cmd_name))
			return ((long)error(err, FATAL, NULL, NULL));
		gc_register(err->gc, err->cmd_name);
		return ((long)error(err, NO_SUCH_FILE, NULL, NULL));
	}
	if (dup2((*redirs)[type], type) == -1)
		return ((long)error(err, FATAL, NULL, NULL));
	return (SUCCESS);
}

/*
**	
*/

char	redir_destroy(int type, int (*redirs)[4], t_err *err)
{
	if ((*redirs)[REAL + type] != -1)
	{
		if (dup2((*redirs)[REAL + type], type) == -1)
			return ((long)error(err, FATAL, NULL, NULL));
		(*redirs)[REAL + type] = -1;
	}
	if ((*redirs)[type] != type)
	{
		if (close((*redirs)[type]) == -1)
			return ((long)error(err, FATAL, NULL, NULL));
		(*redirs)[type] = type;
	}
	return (SUCCESS);
}