/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:48:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/14 18:35:33 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Simple case when next has already a literral value
*/

static t_list	*simple_case(t_list **tokens, t_list **prev, t_list *next)
{
	void	*tmp;

	if (((t_token *)(next->data))->type == TOK_WORD
		|| ((t_token *)(next->data))->type == TOK_NEWLINE)
	{
		if (!(*prev))
		{
			tmp = *tokens;
			*tokens = (*tokens)->next;
			ft_lstdelone(tmp, &token_destroy);
			return (*tokens);
		}
		ft_lstdelone((*prev)->next, &token_destroy);
		(*prev)->next = next;
		return ((*prev)->next);
	}
	return (NULL);
}

/*
**	Change next token to TOK_WORD because TOK_WORD is literal.
**	Delete TOK_BSLASH from list.
*/

t_list	*expand_bslash(t_list **toks, t_list **prev, t_list *next, t_err *err)
{
	t_list	*new;
	char	**str;
	void	*tmp;

	tmp = simple_case(toks, prev, next);
	if (tmp)
		return (tmp);
	if (!ft_strsdup(&str, 1, *(((t_token *)(next->data))->data)))
		return (error(err, MALLOC, (void **)toks, &ft_lstdel));
	if (!new_lstok(TOK_WORD, str, &new))
		return (error(err, MALLOC, (void **)toks, &ft_lstdel));
	tmp = next->next;
	ft_lstdelone(next, &token_destroy);
	new->next = tmp;
	if (!(*prev))
	{
		ft_lstdelone(*toks, &token_destroy);
		*toks = new;
	}
	else
	{
		ft_lstdelone((*prev)->next, &token_destroy);
		(*prev)->next = new;
	}
	return (new);
}
