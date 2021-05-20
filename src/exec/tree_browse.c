/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_browse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:56:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 21:43:36 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Init fd struct.
*/
static void	fd_init(t_fd *fd)
{
	fd->redirs[IN] = STDIN_FILENO;
	fd->redirs[OUT] = STDOUT_FILENO;
	fd->redirs[REAL_IN] = -1;
	fd->redirs[REAL_OUT] = -1;
	fd->pipes[IN] = STDIN_FILENO;
	fd->pipes[OUT] = STDOUT_FILENO;
	fd->pipes[REAL_IN] = -1;
	fd->pipes[REAL_OUT] = -1;
	fd->is_child = 0;
	fd->is_forked = 0;
	fd->is_dad_pipe = 0;
	fd->pid = -1;
}

/*
**	Apply prefix and check return.
*/
static char	my_btree_prefix(t_btree *root, t_fd_env_err *fee,
							char (*f)(void *, t_fd_env_err *))
{
	char	ret;

	if (!(f(root->item, fee)))
		return (FAILURE);
	if (root->left && (!(fee->fd->is_dad_pipe) || !(fee->fd->is_forked)
			|| fee->fd->is_child))
	{
		ret = my_btree_prefix(root->left, fee, f);
		if (!ret)
			return (FAILURE);
	}
	if (root->right && (!(fee->fd->is_dad_pipe) || !(fee->fd->is_forked)
			|| !(fee->fd->is_child)))
	{
		ret = my_btree_prefix(root->right, fee, f);
		if (!ret)
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
**	Return null if no error
*/
char	tree_browse(t_btree *tree, t_list **env, t_err *err)
{
	t_fd_env_err	fee;
	t_fd			fd;

	fd_init(&fd);
	fee = (t_fd_env_err){&fd, env, err};
	if (!my_btree_prefix(tree, &fee, &dispatch))
	{
		if (!redir_destroy(IN, &(fee.fd->redirs), err))
			return (FAILURE);
		if (!redir_destroy(OUT, &(fee.fd->redirs), err))
			return (FAILURE);
		if (!pipe_destroy(fee.fd))
			return ((long)error(err, FATAL, NULL, NULL));
		return (FAILURE);
	}
	if (!redir_destroy(IN, &(fee.fd->redirs), err))
		return (FAILURE);
	if (!redir_destroy(OUT, &(fee.fd->redirs), err))
		return (FAILURE);
	if (!pipe_destroy(fee.fd))
		return ((long)error(err, FATAL, NULL, NULL));
	return (SUCCESS);
}
