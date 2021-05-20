/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:01:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 20:13:55 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ignore TOK_REDIR when creating commands
*/
static int	ignore_redir(t_list **curr, t_list **redirs, t_list **tmp,
						t_list **gc)
{
	t_list	*last;

	if (((t_token *)((*curr)->data))->type != TOK_REDIR)
		return (0);
	if (!(*redirs))
	{
		*redirs = gc_lstnew((*curr)->data, gc);
		if (!*redirs)
			return (-1);
	}
	else
	{
		last = ft_lstlast(*redirs);
		if (last)
		{
			gc_register(gc, last);
			last->next = gc_lstnew((*curr)->data, gc);
			if (!last->next)
				return (-1);
		}
	}
	*tmp = (*curr)->next;
	gc_lstdelone(*curr, NULL, gc);
	*curr = *tmp;
	return (1);
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
static int	create_command(t_list **curr, t_list **redirs, char ***str,
							t_list **gc)
{
	unsigned int	i;
	t_list			*tmp;
	int				ret;

	i = 0;
	*str = (char **)gc_calloc(gc, count_words(*curr) + 1, sizeof(*str));
	if (!(*str))
		return (FAILURE);
	while (((t_token *)((*curr)->data))->type == TOK_WORD
				|| ((t_token *)((*curr)->data))->type == TOK_REDIR)
	{
		ret = ignore_redir(curr, redirs, &tmp, gc);
		if (ret == -1)
			return (FAILURE);
		else if (ret)
			continue ;
		(*str)[i] = gc_strdup(*(((t_token *)((*curr)->data))->data), gc);
		if (!(*str)[i])
			return (FAILURE);
		tmp = (*curr)->next;
		gc_lstdelone((*curr), &token_destroy, gc);
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
	t_list	*last;

	redirs = NULL;
	if (!create_command(curr, &redirs, &str, err->gc))
		return (FAILURE);
	if (!new_lstok(TOK_COMMAND, str, &new, err->gc))
		return (FAILURE);
	new->next = *curr;
	if (redirs)
	{
		new->next = redirs;
		last = ft_lstlast(redirs);
		if (!last)
			return (FAILURE);
		gc_register(err->gc, last);
		last->next = *curr;
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
char	command_merge(t_list **tokens, t_err *err)
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
