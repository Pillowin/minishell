/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:52:10 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 21:54:55 by agautier         ###   ########.fr       */
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
			*((t_token *)(curr->data))->data = gc_strjoin(tmp,
					*((t_token *)(curr->next->data))->data, err->gc);
			gc_free(err->gc, (void **)&(tmp));
			if (!(*((t_token *)(curr->data))->data))
				return ((long)error(err, FATAL, NULL, NULL));
			gc_register(err->gc, *((t_token *)(curr->data))->data);
			tmp = curr->next->next;
			gc_lstdelone(curr->next, &token_destroy, err->gc);
			curr->next = tmp;
			continue ;
		}
		curr = curr->next;
	}
	gc_list_rm_tok_if(tokens, (void *)TOK_SPACE, &is_tok_type, err->gc);
	return (SUCCESS);
}

/*
**	Expand quotes double quotes and backslash
*/

char	expand(t_list **done, t_list **tokens, t_list *env, t_err *err)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *tokens;
	while (curr && ((t_token *)(curr->data))->type != TOK_SEMI)
	{
		if (((t_token *)(curr->data))->type == TOK_QUOTE)
			curr = expand_quote(tokens, &prev, TOK_QUOTE, err);
		else if (((t_token *)(curr->data))->type == TOK_DQUOTE)
			curr = expand_dquote(tokens, &prev, env, err);
		else if (((t_token *)(curr->data))->type == TOK_BSLASH)
			curr = expand_bslash(tokens, &prev, curr->next, err);
		else if (((t_token *)(curr->data))->type == TOK_DOLLAR)
			curr = expand_dollar(tokens, &prev, env, err);
		if (!curr)
			return (FAILURE);
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	*done = *tokens;
	*tokens = NULL;
	if (curr && ((t_token *)(curr->data))->type == TOK_SEMI)
	{
		*tokens = curr->next;
		curr->next = NULL;
		((t_token *)(curr->data))->type = TOK_NEWLINE;
	}
	if (!expand_clean(done, err))
		return (FAILURE);
	return (SUCCESS);
}
