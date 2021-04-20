/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:20:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/18 21:22:24 by agautier         ###   ########.fr       */
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
	if (!my_strdup(data, 2, *(((t_token *)(curr->data))->data)))
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	(*data)[1] = ft_strdup(*(((t_token *)((curr->next)->data))->data));
	if (!((*data)[1]))
	{
		ft_free_tab((void **)(*data));
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	}
	if (!new_lstok(TOK_REDIR, (*data), &redir))
	{
		ft_free_tab((void **)(*data));
		return (error(err, MALLOC, (void **)tokens, &ft_lstdel));
	}
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

int	redir_merge(t_list **tokens, t_err *err)
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
			ft_lstdelone(curr->next, token_destroy);
			ft_lstdelone(curr, token_destroy);
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

int	dgreat_merge(t_list **tokens, t_err *err)
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
			ft_lstdelone(curr->next, token_destroy);
			curr->next = tmp;
			data = ft_strdup(">>");
			if (!data)
				return ((long)error(err, MALLOC, (void **)tokens, &ft_lstdel));
			ft_free((void **)&(*((t_token *)(curr->data))->data));
			*((t_token *)(curr->data))->data = data;
			((t_token *)(curr->data))->type = TOK_DGREAT;
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
