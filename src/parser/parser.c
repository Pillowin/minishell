/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaqug <mamaqug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:23:05 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 262:54 by mamaqautig         ###   ########.fr       */
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

/*
**	Syntax check for each token.
*/

int			check_tokens(t_list *tokens, t_err *err)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*list;
	const int		prios[5] = {
		TOK_SEMI, TOK_PIPE, TOK_DGREAT, TOK_GREAT, TOK_LESS};
	int				(*const check_f[5])(t_list*, unsigned int, t_err*) = {
		check_semi, check_pipe, check_dgreat, check_great, check_less};

	i = 0;
	while (i < 5)
	{
		// my_list_foreach_if(tokens, check_f[i], (void *)&(prios[i]), &cmp);
		// TODO: delete my_foreach_if.c
		list = tokens;
		j = 0;
		while (list)
		{
			if (!cmp(list->data, (int * )&prios[i]))
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

int			parser(t_list **tokens, t_err *err)
{
	if (!expand(tokens, err))
		return (FAILURE);
	if (!dgreat_merge(tokens, err))
		return (FAILURE);
	if (!check_tokens(*tokens, err))
		return (FAILURE);
	if (!redir_merge(tokens, err))
		return (FAILURE);
	if (!command_merge(tokens, err))
		return (FAILURE);
	ft_list_remove_if(tokens, (void *)TOK_NEWLINE, &is_tok_type,
		&token_destroy);
	if (!create_tree(*tokens, err))
		return (FAILURE);
	return (SUCCESS);
}
