/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmamaqquig <mmamaqquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:46 by agautier          #+#    #+#             */
/*   Updated: 2021/03/30 22:14:53 by mmamaqquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/

t_list	*expand_bslash(t_list **tokens, t_list **prev, t_list *next)
{
	t_list		*new;
	t_list		*tmp;
	t_token		*token;
	char		**str;

	if (((t_token *)(next->data))->type == TOK_WORD || ((t_token *)(next->data))->type == TOK_NEWLINE)
	{
		if (!(*prev))
		{
			tmp = (*tokens);
			*tokens = (*tokens)->next;
			ft_lstdelone(tmp, &token_destroy);
			return (*tokens);
		}
		ft_lstdelone((*prev)->next, &token_destroy);
		(*prev)->next = next;
		return ((*prev)->next);
	}
	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
	{
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		error("Memory allocation failed.\n", EXIT_FAILURE);
	}
	*str = ft_strdup(*(((t_token *)(next->data))->data));
	if (!*str)
	{
		ft_free((void **)&str);
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		error("Memory allocation failed.\n", EXIT_FAILURE);
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
		ft_lstdelone(*tokens, &token_destroy);
		*tokens = new;
		return (new);
	}
	ft_lstdelone((*prev)->next, &token_destroy);
	(*prev)->next = new;
	return (new);
}
