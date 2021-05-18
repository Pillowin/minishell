/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmamaqquig <mmamaqquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:04:51 by agautier          #+#    #+#             */
/*   Updated: 2021/05/14 16:26:21 by mmamaqquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_token.
*/

int	token_init(t_tok_type type, char **data, t_token **token, t_list **gc)
{
	if (!my_calloc(1, sizeof(**token), (void **)token, gc))
		return (FAILURE);
	(*token)->type = type;
	(*token)->data = data;
	return (SUCCESS);
}

/*
**	Create new list elem with a token inside.
*/

int	new_lstok(t_tok_type type, char **str, t_list **new, t_list **gc)
{
	t_token	*token;

	if (!token_init(type, str, &token, gc))
		return (FAILURE);
	*new = ft_lstnew(token);
	if (!(*new))
		return (FAILURE);
	gc_register(gc, *new);
	return (SUCCESS);
}

/*
**	Destroy and free a t_token.
*/

void	token_destroy(void *ptr, t_list **gc)
{
	t_token			*token;
	unsigned int	i;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	i = 0;
	while (token->data[i])
	{
		gc_free(gc, (void **)&(token->data[i]));
		i++;
	}
	gc_free(gc, (void **)&(token->data));
	gc_free(gc, (void **)&token);
}
