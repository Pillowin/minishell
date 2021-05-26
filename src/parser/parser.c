/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:11:01 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 17:11:02 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
static t_token	*tokendup(t_token *data, t_list **gc)
{
	t_token			*dest;
	unsigned int	i;

	i = 0;
	dest = (t_token *)gc_calloc(gc, 1, sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->type = data->type;
	while (data->data[i])
		i++;
	dest->data = (char **)gc_calloc(gc, i + 1, sizeof(*(dest->data)));
	if (!(dest->data))
		return (NULL);
	i = 0;
	while (data->data[i])
	{
		dest->data[i] = ft_strdup(data->data[i]);
		if (!(dest->data[i]))
			return (NULL);
		gc_register(gc, dest->data[i]);
		i++;
	}
	return (dest);
}

/*
**	Copy list, remove TOK_SPACE.
**	Init check pointer function table.
*/
static t_list	*init_check(t_list **lst, t_list **gc,
							char (*check_f[5])(t_list *, unsigned int, t_err *))
{
	t_list	*dest;
	t_token	*token;

	dest = NULL;
	while ((*lst))
	{
		token = tokendup((*lst)->data, gc);
		if (!token)
			return (NULL);
		gc_list_push_back(&dest, token, gc);
		(*lst) = (*lst)->next;
	}
	*lst = dest;
	gc_list_rm_tok_if(lst, (void *)TOK_SPACE, &is_tok_type, gc);
	check_f[0] = &check_semi;
	check_f[1] = &check_pipe;
	check_f[2] = &check_dgreat;
	check_f[3] = &check_great;
	check_f[4] = &check_less;
	return (dest);
}

/*
**	Syntax check for each token.
*/
char	check_tokens(t_list *tokens, t_err *err)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*list;
	char			(*check_f[5])(t_list *, unsigned int, t_err *);
	const int		prios[5] = {TOK_SEMI, TOK_PIPE, TOK_DGREAT, TOK_GREAT,
		TOK_LESS};

	if (!init_check(&tokens, err->gc, check_f))
		return ((long)error(err, FATAL, NULL, NULL));
	i = 0;
	while (i < 5)
	{
		list = tokens;
		j = 0;
		while (list)
		{
			if (!cmp_token_type(list->data, (int *)&prios[i]))
				if (!check_f[i](tokens, j, err))
					return (FAILURE);
			list = list->next;
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/*
**	Entry point for parser.
*/
char	parser(t_list **tokens, t_err *err, t_list **env)
{
	t_list	*done;

	if (!dgreat_merge(tokens, err))
		return ((long)error(err, FATAL, NULL, NULL));
	if (!check_tokens(*tokens, err))
		return (FAILURE);
	done = NULL;
	while (*tokens)
	{
		if (!expand(&done, tokens, *env, err))
			return (FAILURE);
		if (!redir_merge(&done, err))
			return ((long)error(err, FATAL, NULL, NULL));
		if (!command_merge(&done, err))
			return ((long)error(err, FATAL, NULL, NULL));
		gc_list_rm_tok_if(&done, (void *)TOK_NEWLINE, &is_tok_type, err->gc);
		if (*tokens && ((t_token *)(*tokens)->data)->data[0][0] == ';')
			return ((long)error(err, SYNTAX_SEMI, NULL, NULL));
		if (!create_tree(done, env, err))
			return (FAILURE);
		done = NULL;
	}
	return (SUCCESS);
}
