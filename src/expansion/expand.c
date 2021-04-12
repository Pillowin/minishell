/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:57:11 by agautier          #+#    #+#             */
/*   Updated: 2021/04/09 22:35:331 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	merge TOK_WORD and Remove TOK_SPACE
*/

static int	expand_clean(t_list** tokens, t_err *err)
{
	t_list	*curr;
	void	*tmp;

	curr = *tokens;
	while (curr)
	{
		if (((t_token *)(curr->data))->type == TOK_WORD && ((t_token *)(curr->next->data))->type == TOK_WORD)
		{
			tmp = *((t_token *)(curr->data))->data;
			*((t_token *)(curr->data))->data = ft_strjoin(tmp, *((t_token *)(curr->next->data))->data);
			if (!(*((t_token *)(curr->data))->data))
			{
				ft_free((void **)&(tmp));
				ft_list_foreach(*tokens, &token_destroy);
				ft_list_clear(*tokens, &ft_free);
				return ((long)error(err, MALLOC, NULL, NULL));
			}
			ft_free((void **)&(tmp));
			tmp = curr->next->next;
			ft_lstdelone(curr->next, &token_destroy);
			curr->next = tmp;
			continue;
		}
		curr = curr->next;
	}
	ft_list_remove_if(tokens, (void *)TOK_SPACE, &is_tok_type, &token_destroy);
	return (SUCCESS);
}

/*
**	Expand quotes double quotes and backslash
**
**	TODO: expand dollar
*/

int	expand(t_list **tokens, t_err *err)
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
			curr = expand_quote(tokens, &prev, next, err);
		else if (((t_token*)(curr->data))->type == TOK_DQUOTE)
			curr = expand_dquote(tokens, &prev, err);
		else if (((t_token*)(curr->data))->type == TOK_BSLASH)
			curr = expand_bslash(tokens, &prev, next, err);
		else if (((t_token*)(curr->data))->type == TOK_DOLLAR)
			expand_dollar();
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	expand_clean(tokens, err);
	return (SUCCESS);
}
