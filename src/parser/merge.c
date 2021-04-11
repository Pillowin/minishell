/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:19:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 15:44:07 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Merge TOK_[LESS | GREAT | DGREAT] and TOK_WORD to TOK_REDIR
*/

void	redir_merge(t_list **tokens)
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
			data = (char **)ft_calloc(2 + 1, sizeof(*data));
			if (!data)
				return ;
			data[0] = ft_strdup(*(((t_token *)((curr)->data))->data));
			data[1] = ft_strdup(*(((t_token *)((curr->next)->data))->data));
			redir = ft_lstnew(token_init(TOK_REDIR, data));
			redir->next = curr->next->next;
			if (prev)
				prev->next = redir;
			else
				*tokens = redir;
			ft_lstdelone(curr->next, token_destroy);
			ft_lstdelone(curr, token_destroy);
			curr = redir;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
}

/*
**	Merge all TOK_WORD qui se suivent
*/

void	command_merge(t_list **tokens)	// TODO: ignorer les tok_redir
{
	t_list			*curr;
	t_list			*prev;
	t_list			*new;
	t_list			*tmp;
	t_list			*redirs;
	char			**str;
	unsigned int	i;

	curr = *tokens;
	prev = NULL;
	while (((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		redirs = NULL;
		i = 0;
		if (((t_token *)(curr->data))->type == TOK_WORD)
		{
			str = (char **)ft_calloc(128 * 128, sizeof(str));	// TODO: count word
			while (((t_token *)(curr->data))->type == TOK_WORD || ((t_token *)(curr->data))->type == TOK_REDIR)
			{
				if (((t_token *)(curr->data))->type == TOK_REDIR)
				{
					if (!redirs)
						redirs = ft_lstnew(curr->data);
					else
						ft_lstlast(redirs)->next = ft_lstnew(curr->data);
					tmp = curr->next;
					ft_lstdelone(curr, NULL);
					curr = tmp;
					continue;
				}
				str[i] = ft_strdup(*(((t_token *)(curr->data))->data));
				tmp = curr->next;
				ft_lstdelone(curr, &token_destroy);
				curr = tmp;
				i++;
			}
			new = ft_lstnew(token_init(TOK_COMMAND, str));
			if (redirs)
			{
				new->next = redirs;
				ft_lstlast(redirs)->next = curr;
			}
			else
				new->next = curr;
			if (!prev)
				*tokens = new;
			else
				prev->next = new;
			continue ;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
}

void	dgreat_merge(t_list **tokens)
{
	t_list	*curr;
	t_list	*tmp;
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
			{
				ft_list_foreach(*tokens, &token_destroy);
				ft_list_clear(*tokens, &ft_free);
				error("Memory allocation failed.\n", EXIT_FAILURE);
			}
			ft_free((void **)&(*((t_token *)(curr->data))->data));
			*((t_token *)(curr->data))->data = data;
			((t_token *)(curr->data))->type = TOK_DGREAT;
		}
		curr = curr->next;
	}
}
