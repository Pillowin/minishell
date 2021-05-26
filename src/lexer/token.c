/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:24:50 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:54:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_token.
*/
int	token_init(t_tok_type type, char **data, t_token **token, t_list **gc)
{
	*token = (t_token *)gc_calloc(gc, 1, sizeof(**token));
	if (!(*token))
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
	*new = gc_lstnew(token, gc);
	if (!(*new))
		return (FAILURE);
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
