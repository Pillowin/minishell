/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:56:21 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/25 18:41:08 by agautier         ###   ########.fr       */
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

int	check_tokens(t_list *tokens, t_err *err)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*list;
	const int		prios[4] = {
		TOK_PIPE, TOK_DGREAT, TOK_GREAT, TOK_LESS};
	int (*	check_f[4])(t_list *, unsigned int, t_err *) = {
		check_pipe, check_dgreat, check_great, check_less};

	i = 0;
	while (i < 4)
	{
		list = tokens;
		j = 0;
		while (list)
		{
			if (!cmp(list->data, (int *)&prios[i]))
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

int	parser(t_list **tokens, t_list **cmds, t_err *err, t_list *env)
{
	t_list	*done;

	done = NULL;
	while (*tokens) // tant que le dernier token est pas \n
	{
		if (!expand(&done, tokens, env, err))
			return (FAILURE);
		if (((t_token *)done->data)->data[0][0] == ';')	//  && !(done->next)
		{
			printf("tu croyé tallé mavoar avec té poing vie regu le ?????????????????\n");
			return (FAILURE);
		}
		if (!dgreat_merge(&done, err))
			return (FAILURE);
		if (!check_tokens(done, err))
			return (FAILURE);
		if (!redir_merge(&done, err))
			return (FAILURE);
		if (!command_merge(&done, err))
			return (FAILURE);
		ft_list_remove_if(&done, (void *)TOK_NEWLINE, &is_tok_type,
			&token_destroy);
		if (!create_tree(done, cmds, err))
			return (FAILURE);
		done = NULL;
	}
	return (SUCCESS);
}
