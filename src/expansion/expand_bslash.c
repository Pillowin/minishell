/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:48:33 by agautier          #+#    #+#             */
/*   Updated: 2021/05/14 19:04:1 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Simple case when next has already a literral value
*/

static t_list	*simple_case(t_list **tokens, t_list **prev, t_list *next,
								t_list **gc)
{
	void	*tmp;

	if (((t_token *)(next->data))->type == TOK_WORD
		|| ((t_token *)(next->data))->type == TOK_NEWLINE)
	{
		if (!(*prev))
		{
			tmp = *tokens;
			*tokens = (*tokens)->next;
			gc_lstdelone(tmp, &token_destroy, gc);
			return (*tokens);
		}
		gc_lstdelone((*prev)->next, &token_destroy, gc);
		(*prev)->next = next;
		return ((*prev)->next);
	}
	return (NULL);
}

/*
**	Change next token to TOK_WORD because TOK_WORD is literal.
**	Delete TOK_BSLASH from list.
*/

t_list	*expand_bslash(t_list **toks, t_list **prev, t_list *next, t_err *err)
{
	t_list	*new;
	char	**str;
	void	*tmp;

	tmp = simple_case(toks, prev, next, err->gc);
	if (tmp)
		return (tmp);
	if (!gc_strsdup(&str, 1, *(((t_token *)(next->data))->data), err->gc))
		return (error(err, FATAL, NULL, NULL));
	if (!new_lstok(TOK_WORD, str, &new, err->gc))
		return (error(err, FATAL, NULL, NULL));
	tmp = next->next;
	gc_lstdelone(next, &token_destroy, err->gc);
	new->next = tmp;
	if (!(*prev))
	{
		gc_lstdelone(*toks, &token_destroy, err->gc);
		*toks = new;
	}
	else
	{
		gc_lstdelone((*prev)->next, &token_destroy, err->gc);
		(*prev)->next = new;
	}
	return (new);
}
