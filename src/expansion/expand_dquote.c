/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:22:25 by agautier          #+#    #+#             */
/*   Updated: 2021/03/30 23:4:39 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/

static int	expand_dquote_bslash(t_list **tokens, t_list **prev, t_err *err)
{
	t_list			*new;
	t_list			*tmp;
	t_list			*curr;
	t_token			*token;
	char			**str;

	if (!(*prev))
		tmp = *tokens;
	else
		tmp = (*prev)->next;
	curr = tmp->next;
	// boucle jusqu'a la dquote
	while (((t_token *)(curr->data))->type != TOK_DQUOTE && ((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		// si bslash
		if (((t_token *)(curr->data))->type == TOK_BSLASH)
		{
			// si next is NOT $ or " or '\'
			if ((((t_token *)(curr->next->data))->type != TOK_DOLLAR)
				&& (((t_token *)(curr->next->data))->type != TOK_DQUOTE)
				&& (((t_token *)(curr->next->data))->type != TOK_BSLASH))
			{	
				// créé TOK_WORD '\' 
				if (!ft_strsdup(&str, 1, "\\"))
				{
					ft_list_foreach(*tokens, &token_destroy);
					ft_list_clear(*tokens, &ft_free);
					return((long)error(err, MALLOC, NULL, NULL));
				}
				// str = (char **)ft_calloc(1 + 1, sizeof(*str));
				// if (!str)
				// {
				// 	ft_list_foreach(*tokens, &token_destroy);
				// 	ft_list_clear(*tokens, &ft_free);
				// 	// error("Memory allocation failed.\n", EXIT_FAILURE);
				// 	return((long)error(err, MALLOC, NULL, NULL));
				// }
				// *str = (char *)ft_calloc(1 + 1, sizeof(**str));
				// if (!*str)
				// {
				// 	ft_free((void **)str);
				// 	ft_list_foreach(*tokens, &token_destroy);
				// 	ft_list_clear(*tokens, &ft_free);
				// 	// error("Memory allocation failed.\n", EXIT_FAILURE);
				// 	return((long)error(err, MALLOC, NULL, NULL));
				// }
				// **str = '\\';
				// token = NULL;
				if (!token_init(TOK_WORD, str, &token))
				{
					ft_free((void **)&(*str));
					ft_free((void **)&str);
					ft_list_foreach(*tokens, &token_destroy);
					ft_list_clear(*tokens, &ft_free);
					// error("Memory allocation failed.\n", EXIT_FAILURE);
					return((long)error(err, MALLOC, NULL, NULL));
				}
				new = ft_lstnew(token);
				if (!new)
				{
					token_destroy(token);
					ft_list_foreach(*tokens, &token_destroy);
					ft_list_clear(*tokens, &ft_free);
					// error("Memory allocation failed.\n", EXIT_FAILURE);
					return((long)error(err, MALLOC, NULL, NULL));
				}
				// mette sur le prev donc avant le TOK_BSLASH
				new->next = curr;
				tmp->next = new;
				curr = expand_bslash(tokens, &new, curr->next, err);
			}
			else
				curr = expand_bslash(tokens, &tmp, curr->next, err);
		}
		tmp = tmp->next;
		curr = curr->next;
	}
	return (SUCCESS);
}

t_list	*expand_dquote(t_list **tokens, t_list **prev, t_err *err)
{
	t_list			*new;
	t_list			*next;
	t_list			*tmp;
	t_token			*token;
	char			**str;
	char			*s;

	if (!(*prev))
		next = (*tokens)->next;
	else
		next = (*prev)->next->next;
	if (!expand_dquote_bslash(tokens, prev, err))
		return (NULL);
	if (!(*prev))
		next = (*tokens)->next;
	else
		next = (*prev)->next->next;
	tmp = next;
	while (((t_token *)(tmp->data))->type != TOK_DQUOTE)
	{
		if (((t_token *)(tmp->data))->type == TOK_NEWLINE)
		{
			ft_list_foreach(*tokens, &token_destroy);
			ft_list_clear(*tokens, &ft_free);
			// error("Undefined case : multiline double quote command.\n", ERR_PARSING);
			return(error(err, MULTILINE_DQUOTE, NULL, NULL));
		}
		tmp = tmp->next;
	}
	if (((t_token *)(next->data))->type == TOK_DQUOTE)
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
			return ((*prev));
		}
	}
	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
	{
		ft_list_foreach(*tokens, &token_destroy);
		ft_list_clear(*tokens, &ft_free);
		// error("Memory allocation failed.\n", EXIT_FAILURE);
		return(error(err, MALLOC, NULL, NULL));
	}
	// *str = (char *)ft_calloc(1 + 1, sizeof(**str));
	// if (!*str)
	// {
	// 	ft_free((void **)str);
	// 	ft_list_foreach(*tokens, &token_destroy);
	// 	ft_list_clear(*tokens, &ft_free);
	// 	error("Memory allocation failed.\n", EXIT_FAILURE);
	// }
	while (((t_token *)(next->data))->type != TOK_DQUOTE)
	{
		// if (((t_token *)(next->data))->type == TOK_NEWLINE)
		// {
		// 	ft_free((void **)&(*str));
		// 	ft_free((void **)str);
		// 	ft_list_foreach(*tokens, &token_destroy);
		// 	ft_list_clear(*tokens, &ft_free);
		// 	error("Undefined case : multiline commands.\n", ERR_PARSING);
		// }
		s = *str;
		*str = ft_strjoin(s, *(((t_token *)(next->data))->data));
		if (!(*str))
		{
			ft_list_foreach(*tokens, &token_destroy);
			ft_list_clear(*tokens, &ft_free);
			// error("Memory allocation failed.\n", EXIT_FAILURE);
			return(error(err, MALLOC, NULL, NULL));
		}
		ft_free((void **)&(s));
		tmp = next->next;
		ft_lstdelone(next, &token_destroy);
		next = tmp;
	}
	// token = NULL;
	token_init(TOK_WORD, str, &token);
	if (!token)
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
