/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:53:00 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 21:53:09 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return an error if this is multiline.
*/

int	check_pair(t_list *curr, t_tok_type type)
{
	while (((t_token *)(curr->data))->type != type)
	{
		if (((t_token *)(curr->data))->type == TOK_NEWLINE)
			return (FAILURE);
		curr = curr->next;
	}
	return (SUCCESS);
}

/*
**	Specific case, when TOK_QUOTES are neighbour, no need to continue
**	quote expansion.
*/

t_list	*case_neighbour(t_list **tokens, t_list *prev, t_list *curr,
						t_list **gc)
{
	t_list	*tmp;

	if (!prev)
	{
		tmp = curr->next;
		gc_lstdelone(curr, &token_destroy, gc);
		((t_token *)((*tokens)->data))->type = TOK_SPACE;
		**((t_token *)((*tokens)->data))->data = ' ';
		(*tokens)->next = tmp;
		return (*tokens);
	}
	tmp = prev->next;
	prev->next = curr->next;
	gc_lstdelone(curr, &token_destroy, gc);
	gc_lstdelone(tmp, &token_destroy, gc);
	return (prev);
}

/*
**	Create a new char * with all data between TOK_QUOTE.
*/

char	**fetch_data(t_list **prev, t_list *curr, t_tok_type type, t_list **gc)
{
	char	**str;
	void	*tmp;

	str = (char **)gc_calloc(gc, 1 + 1, sizeof(*str));
	if (!str)
		return (FAILURE);
	while (((t_token *)(curr->data))->type != type)
	{
		tmp = *str;
		*str = gc_strjoin(tmp, *(((t_token *)(curr->data))->data), gc);
		gc_free(gc, (void **)&(tmp));
		if (!(*str))
			return (FAILURE);
		tmp = curr->next;
		gc_lstdelone(curr, &token_destroy, gc);
		curr = tmp;
	}
	(*prev)->next = curr;
	return (str);
}

/*
**	Remove useless TOK_QUOTE, and add new t_list* TOK_WORD to main list.
*/

t_list	*update_list(t_list **tokens, t_list **prev, t_list *new, t_list **gc)
{
	t_list	*next;
	t_list	*curr;
	void	*tmp;

	curr = *tokens;
	if (*prev)
		curr = (*prev)->next;
	next = curr->next;
	tmp = next->next;
	gc_lstdelone(next, &token_destroy, gc);
	new->next = tmp;
	if (!(*prev))
	{
		gc_lstdelone((*tokens), &token_destroy, gc);
		*tokens = new;
	}
	else
	{
		gc_lstdelone((*prev)->next, &token_destroy, gc);
		(*prev)->next = new;
	}
	return (new);
}

/*
**	Merge TOK_WORD an TOK_SPACE between quotes into a single TOK_WORD and 
**	add it to list.
*/

t_list	*expand_quote(t_list **tokens, t_list **prev, t_tok_type t, t_err *err)
{
	t_list	*curr;
	t_list	*next;
	t_list	*new;
	char	**str;

	curr = *tokens;
	if (*prev)
		curr = (*prev)->next;
	next = curr->next;
	if (!check_pair(next, t))
		return (error(err, MULTILINE_QUOTE, (void **)tokens, &gc_lstdel));
	if (((t_token *)(next->data))->type == t)
		return (case_neighbour(tokens, *prev, next, err->gc));
	str = fetch_data(&curr, next, t, err->gc);
	if (!str)
		return (error(err, FATAL, NULL, NULL));
	if (!new_lstok(TOK_WORD, str, &new, err->gc))
		return (error(err, FATAL, NULL, NULL));
	return (update_list(tokens, prev, new, err->gc));
}
