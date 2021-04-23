/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:38:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/15 16:4446 8 bygautier r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
**	Create a tree from list
*/

int	create_tree(t_list *tokens, t_err *err, t_list *env)
{
	t_btree	*tree;
printf("list=\n");
	ft_list_foreach(tokens, &token_print);
printf("\ntree=\n");
	if (!tokens)
		return (SUCCESS);
	if (!eat_list(tokens, &tree))
	{
		btree_apply_prefix(tree, &token_destroy);
		btree_free(&tree);
		return ((long)error(err, MALLOC, (void **)&tokens, &ft_lstdel));
	}
	exec(tree, env);
	return (SUCCESS);
}
