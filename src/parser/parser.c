/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:56:21 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/14 17:08:527 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Comparer l'enum avec les éléments (token) du tableau.
*/

static int	cmp(t_token *lstdata, int *data)
{
	if ((int)(lstdata->type) == *data)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static t_token	*tokendup(t_token *data, t_list **gc)
{
	t_token 		*dest;
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

static t_list	*lstcpy(t_list *lst, t_list **gc)
{
	t_list	*dest;
	t_token	*token;

	dest = NULL;
	while (lst)
	{
		token = tokendup(lst->data, gc);
		if (!token)
			return (NULL);
		gc_list_push_back(&dest, token, gc);
		lst = lst->next;
	}
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
	t_list			*toks;
	const int		prios[5] = {
		TOK_SEMI, TOK_PIPE, TOK_DGREAT, TOK_GREAT, TOK_LESS};
	char (* const check_f[5])(t_list *, unsigned int, t_err *) = {
		check_semi, check_pipe, check_dgreat, check_great, check_less};
	
	toks = lstcpy(tokens, err->gc);
	if (!toks)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_list_rm_tok_if(&toks, (void *)TOK_SPACE, &is_tok_type, err->gc);
	i = 0;
	while (i < 5)
	{
		list = toks;
		j = 0;
		while (list)
		{
			if (!cmp(list->data, (int *)&prios[i]))
				if (!check_f[i](toks, j, err))
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
	while (*tokens) // tant que le dernier token est pas \n
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
