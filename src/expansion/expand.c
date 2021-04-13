/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:52:10 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/13 17:21:52 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	merge TOK_WORD and Remove TOK_SPACE
*/

static int	expand_clean(t_list **tokens, t_err *err)
{
	t_list	*curr;
	void	*tmp;

	curr = *tokens;
	while (curr)
	{
		if (((t_token *)(curr->data))->type == TOK_WORD
			&& ((t_token *)(curr->next->data))->type == TOK_WORD)
		{
			tmp = *((t_token *)(curr->data))->data;
			*((t_token *)(curr->data))->data = ft_strjoin(tmp,
					*((t_token *)(curr->next->data))->data);
			ft_free((void **)&(tmp));
			if (!(*((t_token *)(curr->data))->data))
				return ((long)error(err, MALLOC, (void **)tokens, &ft_lstdel));
			tmp = curr->next->next;
			ft_lstdelone(curr->next, &token_destroy);
			curr->next = tmp;
			continue ;
		}
		curr = curr->next;
	}
	ft_list_remove_if(tokens, (void *)TOK_SPACE, &is_tok_type, &token_destroy);
	return (SUCCESS);
}

/*
**	Expand quotes double quotes and backslash
**
**	TODO: expand dollar
*/

int	expand(t_list **tokens, t_err *err)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		if (((t_token *)(curr->data))->type == TOK_QUOTE)
			curr = expand_quote(tokens, &prev, curr->next, err);
		else if (((t_token *)(curr->data))->type == TOK_DQUOTE)
			curr = expand_dquote(tokens, &prev, err);
		else if (((t_token *)(curr->data))->type == TOK_BSLASH)
			curr = expand_bslash(tokens, &prev, curr->next, err);
		else if (((t_token *)(curr->data))->type == TOK_DOLLAR)
			expand_dollar();
		if (!curr)
			return (FAILURE);
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	if (!expand_clean(tokens, err))
		return (FAILURE);
	return (SUCCESS);
}
