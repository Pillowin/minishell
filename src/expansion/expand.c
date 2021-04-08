/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggieteer <ggieteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:57:29 by agautier          #+#    #+#             */
/*   Updated: 2021/03/31 16:55:256 byggtiteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_clean_word(t_list **tokens)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	prev = NULL;
	curr = *tokens;
	next = NULL;
	while (curr)
	{
		if (curr->next)
			next = curr->next;
		if (((t_token *)(curr->data))->type == TOK_WORD && ((t_token *)(curr->next->data))->type == TOK_WORD)
		{
			*((t_token *)(curr->data))->data = ft_strjoin(*((t_token *)(curr->data))->data, *((t_token *)(curr->next->data))->data);
			curr->next = curr->next->next;
			//TODO: free curr->next (tmp)
			continue;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
}

/*
**	merge TOK_WORD and Remove TOK_SPACE
*/

static void	expand_clean(t_list** tokens)
{
	expand_clean_word(tokens);
	ft_list_remove_if(tokens, (void *)TOK_SPACE, &is_tok_type, &ft_free);
}

/*
**	Expand quotes double quotes and backslash
**
**	TODO: expand dollar
*/

void	expand(t_list **tokens)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	prev = NULL;
	curr = *tokens;
	next = NULL;
	while (curr)
	{
		if (curr->next)
			next = curr->next;
		if (((t_token*)(curr->data))->type == TOK_QUOTE)
			curr = expand_quote(&prev, next);
		else if (((t_token*)(curr->data))->type == TOK_DQUOTE)
			curr = expand_dquote(&prev);
		else if (((t_token*)(curr->data))->type == TOK_BSLASH)
			curr = expand_bslash(&prev, next);
		else if (((t_token*)(curr->data))->type == TOK_DOLLAR)
			expand_dollar();
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	expand_clean(tokens);
}
