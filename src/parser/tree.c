/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:38:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/15 16:444618 byagtetrerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create a tree from list
*/

char	create_tree(t_list *tokens, t_list **env, t_err *err)
{
	t_btree	*tree;
	char	ret;

	if (!tokens)
		return (SUCCESS);
	if (!eat_list(tokens, &tree, err->gc))
		return ((long)error(err, FATAL, NULL, NULL));
	btree_apply_prefix(tree, &token_print);
	g_exit_status = 0;
	ret = SUCCESS;
	if (!exec(tree, env, err))
		ret = FAILURE;
	gc_btree_apply_prefix(tree, &token_destroy, err->gc);
	gc_btree_free(&tree, err->gc);
	return (ret);
}
