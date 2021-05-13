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

int	create_tree(t_list *tokens, t_list *env, t_err *err)
{
	t_btree	*tree;

	if (!tokens)
		return (SUCCESS);
	if (!eat_list(tokens, &tree))
	{
		btree_apply_prefix(tree, &token_destroy);
		btree_free(&tree);
		return ((long)error(err, MALLOC, (void **)&tokens, &ft_lstdel));
	}
	g_exit_status = 0;
	if (!exec(tree, env, err))
	{
		// ft_putstr_fd("minishell: 3", STDERR_FILENO);	// TODO:
		// ft_putstr_fd(err->cmd_name, STDERR_FILENO);
		// ft_putstr_fd(": ", STDERR_FILENO);
		// if (err->code == ERR_NO)
		// 	ft_putstr_fd(strerror(errno), STDERR_FILENO);
		// else
		// 	ft_putstr_fd(err->message[err->code], STDERR_FILENO);
		// ft_putchar_fd('\n', STDERR_FILENO);
		int tmp = dup(STDOUT_FILENO);
		dup2(STDERR_FILENO, STDOUT_FILENO);			// TODO: message pour cd et export avec les « toto+toto=tonton »
		if (err->code == ERR_NO)
			printf("minishell (tree): %s: %s\n", err->cmd_name, strerror(errno));	// TODO: remove tree
		else
			printf("minishell (tree): %s: %s\n", err->cmd_name, err->message[err->code]);
		dup2(tmp, STDOUT_FILENO);
		ft_free((void **)&(err->cmd_name));
	}
	return (SUCCESS);
}
