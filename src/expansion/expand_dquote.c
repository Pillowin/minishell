/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:00:48 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/14 18:57:559 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	If next token is TOK_DOLLAR, TOK_DQUOTE or TOK_BSLASH,
**	push a new TOK_BSLASH to list.
*/

static int	push_bslash(t_list **curr, t_list *next, t_err *err)
{
	t_list	*new;
	char	**str;

	if ((((t_token *)(next->next->data))->type != TOK_DOLLAR)
		&& (((t_token *)(next->next->data))->type != TOK_DQUOTE)
		&& (((t_token *)(next->next->data))->type != TOK_BSLASH))
	{
		if (!gc_strsdup(&str, 1, "\\", err->gc))
			return (FAILURE);
		if (!new_lstok(TOK_WORD, str, &new, err->gc))
			return (FAILURE);
		new->next = next;
		(*curr)->next = new;
		(*curr) = (*curr)->next;
	}
	return (SUCCESS);
}

/*
**	Expand TOK_BLASH between double quotes.
*/

static int	expand_dquote_bslash(t_list **tokens, t_list **prev, t_err *err)
{
	t_list	*curr;
	t_list	*next;

	if (!(*prev))
		curr = *tokens;
	else
		curr = (*prev)->next;
	next = curr->next;
	while (((t_token *)(next->data))->type != TOK_DQUOTE
		&& ((t_token *)(next->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(next->data))->type == TOK_BSLASH)
		{
			if (!push_bslash(&curr, next, err))
				return ((long)error(err, FATAL, NULL, NULL));
			next = expand_bslash(tokens, &curr, next->next, err);
			if (!next)
				return (FAILURE);
		}
		curr = curr->next;
		next = next->next;
	}
	return (SUCCESS);
}

/*
**	Expand TOK_DOLLAR between double quotes.
*/
// TODO: test a liiiiiitle more
static int	expand_dquote_dollar(t_list **tokens, t_list **prev, t_list *env, t_err *err)
{
	t_list	*curr;
	t_list	*next;

	if (!(*prev))
		curr = *tokens;
	else
		curr = (*prev)->next;
	next = curr->next;
	while (((t_token *)(next->data))->type != TOK_DQUOTE
		&& ((t_token *)(next->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(next->data))->type == TOK_DOLLAR)
		{
			curr = expand_dollar(tokens, &curr, env, err);
			if (!curr)
				return (FAILURE);
		}
		curr = curr->next;
		next = curr->next;
	}
	return (SUCCESS);
}

/*
**	Merge TOK_WORD an TOK_SPACE between quotes into a single TOK_WORD and
**	add it to list.
*/

t_list	*expand_dquote(t_list **tokens, t_list **prev, t_list *env, t_err *err)
{
	if (!expand_dquote_bslash(tokens, prev, err))
		return (NULL);
	if (!expand_dquote_dollar(tokens, prev, env, err))
		return (NULL);
	return (expand_quote(tokens, prev, TOK_DQUOTE, err));
}
