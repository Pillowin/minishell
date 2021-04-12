/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:48:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 20:50:43 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/

t_list	*expand_bslash(t_list **tokens, t_list **prev, t_list *next, t_err *err)
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
	if (!ft_strsdup(&str, 1, *(((t_token *)(next->data))->data)))
	{
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		return(error(err, MALLOC, NULL, NULL));
	}
	// str = (char **)ft_calloc(1 + 1, sizeof(*str));
	// if (!str)
	// {
	// 	ft_list_foreach(*tokens, &token_destroy);
	// 	ft_list_clear(*tokens, &ft_free);
	// 	// error("Memory allocation failed.\n", EXIT_FAILURE);
	// 	return(error(err, MALLOC, NULL, NULL));
	// }
	// *str = ft_strdup(*(((t_token *)(next->data))->data));
	// if (!*str)
	// {
	// 	ft_free((void **)&str);
	// 	ft_list_foreach(*tokens, &token_destroy);
	// 	// error("Memory allocation failed.\n", EXIT_FAILURE);
	// 	return(error(err, MALLOC, NULL, NULL));
	// }
	// token = NULL;
	if (!token_init(TOK_WORD, str, &token))
	{
		ft_free((void **)&(*str));
		ft_free((void **)&str);
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		// error("Memory allocation failed.\n", EXIT_FAILURE);
		return(error(err, MALLOC, NULL, NULL));
	}
	new = ft_lstnew(token);
	if (!new)
	{
		token_destroy(token);
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		// error("Memory allocation failed.\n", EXIT_FAILURE);
		return(error(err, MALLOC, NULL, NULL));
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
