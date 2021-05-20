/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:41:35 by agautier          #+#    #+#             */
/*   Updated: 2021/04/27 17:3144 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Handle $?
*/
static t_list	*question_mark(t_list **curr, t_list **next, t_err *err)
{
	char	**next_data_data;
	char	*new_str;
	char	*str;
	void	*tmp;
	t_token	*curr_data;

	curr_data = (t_token *)((*curr)->data);
	next_data_data = (((t_token *)((*next)->data))->data);
	if ((*next_data_data)[0] != '?')
		return (NULL);
	curr_data->type = TOK_WORD;
	gc_free(err->gc, (void **)(curr_data->data));
	new_str = ft_itoa(g_exit_status & 0x00FF);
	if (!new_str)
		return (error(err, FATAL, NULL, NULL));
	gc_register(err->gc, new_str);
	*(curr_data->data) = new_str;
	if ((*next_data_data)[1])
	{
		str = ft_substr(*next_data_data, 1, ft_strlen(*next_data_data) - 1);
		if (!str)
			return (error(err, FATAL, NULL, NULL));
		gc_register(err->gc, str);
		gc_free(err->gc, (void **)next_data_data);
		*next_data_data = str;
		return (*curr);
	}
	tmp = (*next)->next;
	gc_lstdelone((*next), &token_destroy, err->gc);
	(*curr)->next = tmp;
	return (*curr);
}

/*
**	Handle specific case for (d)quotes and special char
*/
static t_list	*specific_case(t_list **prev, t_list *curr, t_list *next,
								t_list **gc)
{
	if (((t_token *)next->data)->type != TOK_WORD
		|| !is_name(*(((t_token *)(next->data))->data), '\n'))
	{
		if (((t_token *)next->data)->type == TOK_QUOTE
			|| ((t_token *)next->data)->type == TOK_DQUOTE)
		{
			if (*prev)
			{
				gc_lstdelone(curr, &token_destroy, gc);
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
	t_list	*new;

	if (is_name(*(((t_token *)next->data)->data), '\n'))
		*name = *((t_token *)next->data)->data;
	else
	{
		*name = fetch_name(((t_token *)next->data)->data, err);
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
	new = question_mark(&curr, &next, err);
	if (new)
		return (new);
	new = specific_case(prev, curr, next, err->gc);
	if (new)
		return (new);
	new = get_var(next, &name, env, err);
	if (!new)
		return (error(err, FATAL, NULL, NULL));
	if (!ft_strcmp(name, *(((t_token *)(next->data))->data)))
		gc_lstdelone(next, &token_destroy, err->gc);
	gc_lstdelone(curr, &token_destroy, err->gc);
	if (*prev)
	{
		(*prev)->next = new;
		return (*prev);
	}
	*toks = new;
	return (*toks);
}
