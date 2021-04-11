/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:46:53 by agautier          #+#    #+#             */
/*   Updated: 2021/04/09 17:20:4 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/

t_list	*expand_quote(t_list **tokens, t_list **prev, t_list *next)
{
	t_list			*new;
	t_list			*tmp;
	t_token			*token;
	char			**str;
	char			*s;




	tmp = next;
	while (((t_token *)(tmp->data))->type != TOK_QUOTE)
	{
		if (((t_token *)(tmp->data))->type == TOK_NEWLINE)
		{
			ft_list_foreach(*tokens, &token_destroy);
			ft_list_clear(*tokens, &ft_free);
			error("Undefined case : multiline quote command.\n", ERR_PARSING);
		}
		tmp = tmp->next;
	}
	if (((t_token *)(next->data))->type == TOK_QUOTE)
	{
		if (!(*prev))
		{
			tmp = next->next;
			ft_lstdelone(next, &token_destroy);
			((t_token *)((*tokens)->data))->type = TOK_SPACE;
			**((t_token *)((*tokens)->data))->data = ' ';
			(*tokens)->next = tmp;
			return (*tokens);
		}
		else
		{
			tmp = (*prev)->next;
			(*prev)->next = next->next;
			ft_lstdelone(next, &token_destroy);
			ft_lstdelone(tmp, &token_destroy);
			return (*prev);
		}
	}
	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
	{
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		error("Memory allocation failed.\n", EXIT_FAILURE);
	}
	// *str = (char *)ft_calloc(1 + 1, sizeof(**str));
	// if (!*str)
	// {
	// 	ft_free((void **)&str);
	// 	ft_list_clear(*tokens, &token_destroy);
	// 	error("Memory allocation failed.\n", EXIT_FAILURE);
	// }
	while (((t_token *)(next->data))->type != TOK_QUOTE)
	{
		s = *str;
		*str = ft_strjoin(s, *(((t_token *)(next->data))->data));
		if (!(*str))
		{
			ft_free((void **)&(s));
			ft_list_foreach(*tokens, &token_destroy);
			ft_list_clear(*tokens, &ft_free);
			error("Memory allocation failed.\n", EXIT_FAILURE);
		}
		ft_free((void **)&(s));
		tmp = next->next;
		ft_lstdelone(next, &token_destroy);
		next = tmp;
	}
	token = token_init(TOK_WORD, str);
	if (!token)
	{
		ft_free((void **)&(*str));
		ft_free((void **)&str);
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		error("Memory allocation failed.\n", EXIT_FAILURE);
	}
	new = ft_lstnew(token);
	if (!new)
	{
		token_destroy(token);
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		error("Memory allocation failed.\n", EXIT_FAILURE);
	}
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
