/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:20:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/14 17:0051 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create a new list elem TOK_REDIR
*/

static t_list	*create_redir(t_list **tokens, t_list **prev, char ***data,
								 t_err *err)
{
	t_list	*redir;
	t_list	*curr;

	curr = *tokens;
	if (*prev)
		curr = (*prev)->next;
	if (!gc_strsdup(data, 2, *(((t_token *)(curr->data))->data), err->gc))
		return (NULL);
	(*data)[1] = ft_strdup(*(((t_token *)((curr->next)->data))->data));
	if (!((*data)[1]))
		return (NULL);
	if (!new_lstok(TOK_REDIR, (*data), &redir, err->gc))
		return (NULL);
	gc_register(err->gc, (*data)[1]);
	redir->next = curr->next->next;
	if ((*prev))
		(*prev)->next = redir;
	else
		*tokens = redir;
	return (redir);
}

/*
**	Merge TOK_[LESS | GREAT | DGREAT] and TOK_WORD to TOK_REDIR
*/

char	redir_merge(t_list **tokens, t_err *err)
{
	t_list	*curr;
	t_list	*redir;
	t_list	*prev;
	char	**data;

	prev = NULL;
	curr = *tokens;
	while (curr && ((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(curr->data))->type == TOK_DGREAT
			|| ((t_token *)(curr->data))->type == TOK_GREAT
			|| ((t_token *)(curr->data))->type == TOK_LESS)
		{
			redir = create_redir(tokens, &prev, &data, err);
			if (!redir)
				return (FAILURE);
			gc_lstdelone(curr->next, token_destroy, err->gc);
			gc_lstdelone(curr, token_destroy, err->gc);
			curr = redir;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	return (SUCCESS);
}

/*
**	Merge pairs of TOK_GREAT to a single TOK_DGREAT
*/

char	dgreat_merge(t_list **tokens, t_err *err)
{
	t_list	*curr;
	void	*tmp;
	char	*data;

	curr = *tokens;
	while (((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(curr->data))->type == TOK_GREAT
				&& ((t_token *)(curr->next->data))->type == TOK_GREAT)
		{
			tmp = curr->next->next;
			gc_lstdelone(curr->next, token_destroy, err->gc);
			curr->next = tmp;
			data = ft_strdup(">>");
			if (!data)
				return (FAILURE);
			gc_register(err->gc, data);
			gc_free(err->gc, (void **)&(*((t_token *)(curr->data))->data));
			*((t_token *)(curr->data))->data = data;
			((t_token *)(curr->data))->type = TOK_DGREAT;
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
