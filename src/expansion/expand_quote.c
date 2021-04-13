/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:42:57 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/13 22:47:29 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return an error if this is multiline.
*/

static int	check_pair(t_list **tokens, t_list *curr, t_err *err)
{
	while (((t_token *)(curr->data))->type != TOK_QUOTE)
	{
		if (((t_token *)(curr->data))->type == TOK_NEWLINE)
			return ((long)error(err, MULTILINE_QUOTE,
					(void **)tokens, &ft_lstdel));
		curr = curr->next;
	}
	return (SUCCESS);
}

/*
**	Specific case, when TOK_QUOTES are neighbour, no need to continue
**	quote expansion.
*/

static t_list	*case_neighbour(t_list **tokens, t_list *prev, t_list *curr)
{
	t_list	*tmp;

	if (!prev)
	{
		tmp = curr->next;
		ft_lstdelone(curr, &token_destroy);
		((t_token *)((*tokens)->data))->type = TOK_SPACE;
		**((t_token *)((*tokens)->data))->data = ' ';
		(*tokens)->next = tmp;
		return (*tokens);
	}
	tmp = prev->next;
	prev->next = curr->next;
	ft_lstdelone(curr, &token_destroy);
	ft_lstdelone(tmp, &token_destroy);
	return (prev);
}

/*
**	Create a new char * with all data between TOK_QUOTE.
*/

static int	fetch_data(t_list **prev, t_list **curr, char ***str)
{
	void	*tmp;

	(*str) = (char **)ft_calloc(1 + 1, sizeof(*(*str)));
	if (!(*str))
		return (FAILURE);
	while (((t_token *)((*curr)->data))->type != TOK_QUOTE)
	{
		tmp = *(*str);
		*(*str) = ft_strjoin(tmp, *(((t_token *)((*curr)->data))->data));
		ft_free((void **)&(tmp));
		if (!(*(*str)))
		{
			ft_free((void **)&(*str));
			return (FAILURE);
		}
		tmp = (*curr)->next;
		ft_lstdelone(*curr, &token_destroy);
		*curr = tmp;
	}
	(*prev)->next = *curr;
	return (SUCCESS);
}

/*
**	Remove useless TOK_QUOTE, and add new t_list* TOK_WORD to main list.
*/

static t_list	*update_list(t_list **tokens, t_list **prev, t_list *curr,
								t_list *new)
{
	t_list	*next;
	void	*tmp;

	next = curr->next;
	tmp = next->next;
	ft_lstdelone(next, &token_destroy);
	new->next = tmp;
	if (!(*prev))
	{
		ft_lstdelone((*tokens), &token_destroy);
		(*tokens) = new;
	}
	else
	{
		ft_lstdelone((*prev)->next, &token_destroy);
		(*prev)->next = new;
	}
	return (new);
}

/*
**	Merge TOK_WORD an TOK_SPACE between quotes into a single TOK_WORD and 
**	add it to list.
*/

t_list	*expand_quote(t_list **tokens, t_list **prev, t_list *next, t_err *err)
{
	t_list	*curr;
	t_list	*new;
	t_token	*token;
	char	**str;

	curr = *tokens;
	if (*prev)
		curr = (*prev)->next;
	if (!check_pair(tokens, next, err))
		return (NULL);
	if (((t_token *)(next->data))->type == TOK_QUOTE)
		return (case_neighbour(tokens, *prev, next));
	if (!fetch_data(&curr, &next, &str))
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	if (!token_init(TOK_WORD, str, &token))
	{
		ft_free_tab((void **)str);
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	}
	new = ft_lstnew(token);
	if (!new)
		token_destroy(token);
	if (!new)
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	return (update_list(tokens, prev, curr, new));
}
