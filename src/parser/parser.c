/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/08 17:14:563 byggieteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Comparer l'enum avec les éléments (token) du tableau.
*/

static int	cmp_lstdata_data(t_token *lstdata, int *data)
{
	if ((int)(lstdata->type) == *data)
		return (0);
	return (1);
}

/*
**	Syntax check for each token.
*/

void	check_tokens(t_list *tokens)
{
	const int		prios[5] = {TOK_SEMI, TOK_PIPE, TOK_DGREAT, TOK_GREAT, TOK_LESS};
	void			(*const check_f[5])(t_list*, unsigned int) = {check_semi, check_pipe, check_dgreat, check_great, check_less};
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		my_list_foreach_if(tokens, check_f[i], (void *)&(prios[i]), cmp_lstdata_data);
		i++;
	}
}

/*
**	Update list
**
**	TODO: regrouper les tokens pour faire des t_command et t_redir
**	TODO: creer arbre
*/

void	parse_tokens(t_list **tokens)
{
	// TODO: great merge
	expand(tokens);
	dgreat_merge(tokens);
	check_tokens(*tokens);
	redir_merge(tokens);
	printf("\n-----------------------------------------\n\tCreating list\n\n");
	ft_list_foreach(*tokens, &token_print);
	command_merge(tokens);
	printf("\n-----------------------------------------\n\tCommand merged\n\n");
	ft_list_foreach(*tokens, &token_print);
	ft_list_remove_if(tokens, (void *)TOK_NEWLINE, &is_tok_type, &token_destroy);
	create_tree(*tokens);
}
