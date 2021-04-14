/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:01:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/14 23:24:19 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ignore TOK_REDIR when creating commands
*/

static int	ignore_redir(t_list **curr, t_list **redirs, t_list **tmp)
{
	if (((t_token *)((*curr)->data))->type == TOK_REDIR)
	{
		if (!(*redirs))
			*redirs = ft_lstnew((*curr)->data);
		else
			ft_lstlast(*redirs)->next = ft_lstnew((*curr)->data);
		*tmp = (*curr)->next;
		ft_lstdelone((*curr), NULL);
		*curr = *tmp;
		return (1);
	}
	return (0);
}

/*
**	Count TOK_WORDS
*/

static unsigned int	count_words(t_list *tokens)
{
	unsigned int	i;

	i = 0;
	while (tokens && (((t_token *)(tokens->data))->type == TOK_WORD
		|| ((t_token *)(tokens->data))->type == TOK_REDIR))
	{
		if (((t_token *)(tokens->data))->type == TOK_WORD)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

/*
**	Merge TOK_WORDS into a TOK_COMMAND
*/

static int	create_command(t_list **curr, t_list **redirs, char ***str)
{
	unsigned int	i;
	t_list			*tmp;

	i = 0;
	*str = (char **)ft_calloc(count_words(*curr) + 1, sizeof(*str));
	if (!(*str))
		return (FAILURE);
	while (((t_token *)((*curr)->data))->type == TOK_WORD
				|| ((t_token *)((*curr)->data))->type == TOK_REDIR)
	{
		if (ignore_redir(curr, redirs, &tmp))
			continue ;
		(*str)[i] = ft_strdup(*(((t_token *)((*curr)->data))->data));
		if (!(*str)[i])
		{
			ft_free((void **)&(**str));
			return (FAILURE);
		}
		tmp = (*curr)->next;
		ft_lstdelone((*curr), &token_destroy);
		(*curr) = tmp;
		i++;
	}
	return (SUCCESS);
}

/*
**	Add TOK_COMMAND to list
*/

static int	add_cmd_to_lst(t_list **tokens, t_list **prev, t_list **curr,
							t_err *err)
{
	t_list	*new;
	t_list	*redirs;
	char	**str;

	redirs = NULL;
	if (!create_command(curr, &redirs, &str))
		return ((long)error(err, MALLOC, NULL, NULL));
	if (!new_lstok(TOK_COMMAND, str, &new))
	{
		ft_free_tab((void **)str);
		return ((long)error(err, MALLOC, (void **)tokens, &ft_lstdel));
	}
	new->next = *curr;
	if (redirs)
	{
		new->next = redirs;
		ft_lstlast(redirs)->next = *curr;
	}
	if (!(*prev))
		*tokens = new;
	else
		(*prev)->next = new;
	return (SUCCESS);
}

/*
**	Merge all TOK_WORD qui se suivent
*/

int	command_merge(t_list **tokens, t_err *err)
{
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = *tokens;
	while (((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(curr->data))->type == TOK_WORD)
		{
			if (!add_cmd_to_lst(tokens, &prev, &curr, err))
				return (FAILURE);
			continue ;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
	return (SUCCESS);
}
