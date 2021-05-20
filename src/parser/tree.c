/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:43:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 19:43:36 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create a tree from list
*/
char	create_tree(t_list *tokens, t_list **env, t_err *err)
{
	t_btree	*tree;

	if (!tokens)
		return (SUCCESS);
	if (!eat_list(tokens, &tree, err->gc))
		return ((long)error(err, FATAL, NULL, NULL));
	if (!tree_browse(tree, env, err))
	{
		if (err->code == FATAL)
			return (FAILURE);
		if (err->code == ERR_NO)
			perr_msg(err->cmd_name, NULL, strerror(errno), err->gc);
		else if (err->code != NONE)
			perr_msg(err->cmd_name, NULL, err->message[err->code], err->gc);
	}
	gc_btree_apply_prefix(tree, &token_destroy, err->gc);
	gc_btree_free(&tree, err->gc);
	return (SUCCESS);
}
