/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:41:35 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 00:22:43 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Handle specific case for (d)quotes and special char
*/

static t_list	*specific_case(t_list **prev, t_list *curr, t_list *next)
{
	if (((t_token *)next->data)->type != TOK_WORD
		|| !is_name(*(((t_token *)(next->data))->data), '\n'))
	{
		if (((t_token *)next->data)->type == TOK_QUOTE
			|| ((t_token *)next->data)->type == TOK_DQUOTE)
		{
			if (*prev)
			{
				ft_lstdelone(curr, &token_destroy);
				(*prev)->next = next;
				return (*prev);
			}
			((t_token *)curr->data)->type = TOK_SPACE;
			return (curr);
		}
		if (!ft_isalpha(*(((t_token *)(next->data))->data)[0])
			&& (*(((t_token *)(next->data))->data)[0]) != '_')
		{
			((t_token *)curr->data)->type = TOK_WORD;
			return (curr);
		}
	}
	return (NULL);
}


/*
**	Fetch var name
**	Fetch var value
*/

static t_list	*get_var(t_list *next, char **name, t_list *env, t_err *err)
{
	t_list *new;

	if (is_name(*(((t_token *)next->data)->data), '\n'))
		*name = *((t_token *)next->data)->data;
	else
	{
		*name = fetch_name(((t_token *)next->data)->data);
		if (!(*name))
			return (NULL);
	}
	new = fetch_value(next, *name, env, err);
	if (!new)
		return (NULL);
	return (new);
}

/*
**	Replace env var by his content (only TOK_WORD and TOK_SPACE)
**	// TODO: $?
*/
t_list	*expand_dollar(t_list **toks, t_list **prev, t_list *env, t_err *err)
{
	t_list	*curr;
	t_list	*next;
	t_list	*new;
	char	*name;

	curr = *toks;
	if (*prev)
		curr = (*prev)->next;
	next = curr->next;
	new = specific_case(prev, curr, next);
	if (new)
		return (new);
	new = get_var(next, &name, env, err);
	if (!new)
		return (NULL);
	if (!ft_strcmp(name, *(((t_token *)(next->data))->data)))
		ft_lstdelone(next, &token_destroy);
	ft_lstdelone(curr, &token_destroy);
	if (*prev)
		(*prev)->next = new;
	else
		*toks = new;
	return (new);
}
