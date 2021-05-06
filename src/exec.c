/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:38:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/24 208:04406 byggeeteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: free dans les err malloc


/*
**	
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
**
*/

static char	my_btree_prefix(t_btree *root, t_fd_env_err *fd_env_err, char (*f)(void *, t_fd_env_err *))
{
	char	ret;
	
	if (!(f(root->item, fd_env_err)))
		return (FAILURE);
	if (root->left && (!(fd_env_err->fd->is_dad_pipe) || !(fd_env_err->fd->is_forked) || fd_env_err->fd->is_child))
	{
		ret = my_btree_prefix(root->left, fd_env_err, f);
		if (!ret)
			return (FAILURE);
	}
	if (root->right && (!(fd_env_err->fd->is_dad_pipe) || !(fd_env_err->fd->is_forked) || !(fd_env_err->fd->is_child)))
	{
		ret = my_btree_prefix(root->right, fd_env_err, f);
		if (!ret)
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
**
*/

static char	exec_cmd(t_token *token, t_fd *fd, t_list *env, t_err *err)
{
	char	*path;
	int		ret;
	t_stat	buf;

	err->cmd_name = ft_strdup(token->data[0]);
	if (!(err->cmd_name))
		return (FAILURE);
	ret = is_builtin(token, fd, env, err);
	if (!ret)
		return (FAILURE);
	else if (ret == DONE)
		return (SUCCESS);
	if (token->data[0][0] == '/')
	{
		path = binary_absolute_path(token, err);
		if (!path)
			return (FAILURE);
	}
	else if (token->data[0][0] == '.')
	{
		path = binary_relative_path(token, err);
		if (!path)
			return (FAILURE);
	}
	else
	{
		path = binary_not_a_path(token, &buf, env, err);
		if (!path)
			return (FAILURE);
	}
	if (!binary_exec(token, path, fd, env))
		return ((long)error(err, ERRNO, NULL, NULL));
	ft_free((void **)&path);
	return (SUCCESS);
}

/*
**
*/

static char	dispatch(void *item, t_fd_env_err *fd_env_err)
{
	t_token	*token;

	token = (t_token *)item;
	if (token->type == TOK_PIPE)
	{
		if (!pipe_init(fd_env_err->fd))
			return ((long)error(fd_env_err->err, ERRNO, NULL, NULL));
			fd_env_err->fd->is_dad_pipe = 1;
	}
	else if (token->type == TOK_REDIR)
	{
		if (!redir_init(token, &(fd_env_err->fd->redirs)))
			return ((long)error(fd_env_err->err, ERRNO, NULL, NULL));
		fd_env_err->fd->is_dad_pipe = 0;

	}
	else if (token->type == TOK_COMMAND)
	{
		if (!exec_cmd(token, fd_env_err->fd, fd_env_err->env, fd_env_err->err))
			return (FAILURE);
		if (!redir_destroy(IN, &(fd_env_err->fd->redirs)))
			return (FAILURE);
		if (!redir_destroy(OUT, &(fd_env_err->fd->redirs)))
			return (FAILURE);
		fd_env_err->fd->is_dad_pipe = 0;
	}
	return (SUCCESS);
}


/*
**	Return null if no error
*/

char	exec(t_btree *tree, t_list *env, t_err *err)
{
	t_fd			fd;
	t_fd_env_err	fd_env_err;

	// btree_apply_prefix(tree, &token_print);
	// ft_putendl_fd("\n", STDERR_FILENO);

	fd_init(&fd);
	fd_env_err = (t_fd_env_err){&fd, env, err};
	if (!my_btree_prefix(tree, &fd_env_err, &dispatch))
		return (FAILURE);
	if (!pipe_destroy(fd_env_err.fd))
		return ((long)error(err, ERRNO, NULL, NULL));
	// btree_apply_prefix(tree, &token_print);

	btree_apply_prefix(tree, &token_destroy);
	btree_free(&tree);
	return (SUCCESS);
}
