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

static char	my_btree_prefix(t_btree *root, t_fd_env_err *fee, char (*f)(void *, t_fd_env_err *))
{
	char	ret;
	
	if (!(f(root->item, fee)))
		return (FAILURE);
	if (root->left && (!(fee->fd->is_dad_pipe) || !(fee->fd->is_forked) || fee->fd->is_child))
	{
		ret = my_btree_prefix(root->left, fee, f);
		if (!ret)
			return (FAILURE);
	}
	if (root->right && (!(fee->fd->is_dad_pipe) || !(fee->fd->is_forked) || !(fee->fd->is_child)))
	{
		ret = my_btree_prefix(root->right, fee, f);
		if (!ret)
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
**
*/

static char	exec_cmd(t_token *token, t_fd *fd, t_list **env, t_err *err)
{
	char			*path;
	int				ret;
	t_stat			buf;
	t_fd_env_err	*fee;

	fee = &((t_fd_env_err){fd, env, err});
	// fee->err->cmd_name = ft_strdup(token->data[0]);
	// if (!(fee->err->cmd_name))
	// 	return ((long)error(err, FATAL, NULL, NULL));
	// gc_register(err->gc, err->cmd_name);
	ret = is_builtin(token, fee->fd, fee->env, fee->err);
	if (!ret)
		return (FAILURE);
	else if (ret == DONE)
		return (SUCCESS);
	if (token->data[0][0] == '/')
	{
		path = binary_absolute_path(token, fee->err);
		if (!path)
			return ((long)error(err, ERR_NO, NULL, NULL));
	}
	else if (token->data[0][0] == '.')
	{
		path = binary_relative_path(token, fee->err);
		if (!path)
			return ((long)error(err, ERR_NO, NULL, NULL));
	}
	else
	{
		path = binary_not_a_path(token, &buf, *env, fee->err);
		if (!path)
			return (FAILURE);
	}
	if (!binary_exec(token, path, fee))
	{
		gc_free(fee->err->gc, (void **)&path);
		return (FAILURE);
	}
	gc_free(fee->err->gc, (void **)&path);
	return (SUCCESS);
}

/*
**
*/

static char	dispatch(void *item, t_fd_env_err *fee)
{
	t_token	*token;

	token = (t_token *)item;
	if (token->type == TOK_PIPE)
	{
		if (!pipe_init(fee->fd))
			return ((long)error(fee->err, ERR_NO, NULL, NULL));
		fee->fd->is_dad_pipe = 1;
	}
	else if (token->type == TOK_REDIR)
	{
		if (!redir_init(token, &(fee->fd->redirs), fee->err))
		{
			if (!redir_destroy(IN, &(fee->fd->redirs), fee->err))
				return (FAILURE);
			if (!redir_destroy(OUT, &(fee->fd->redirs), fee->err))
				return (FAILURE);
			if (fee->fd->is_child)
			{
				if (fee->err->code == ERR_NO)
					print_err_msg(fee->err->cmd_name, NULL, strerror(errno), fee->err->gc);
				else
					print_err_msg(fee->err->cmd_name, NULL, fee->err->message[fee->err->code], fee->err->gc);
				gc_clean(fee->err->gc);
				exit(g_exit_status & 0x00FF);
			}
			return (FAILURE);
		}
		fee->fd->is_dad_pipe = 0;
	}
	else if (token->type == TOK_COMMAND)
	{
		if (fee->fd->pipes[REAL_IN] == -1 && fee->fd->pipes[REAL_OUT] == -1)
			waitpid(-1, NULL, 0);
		fee->err->cmd_name = ft_strdup(token->data[0]);
		if (!(fee->err->cmd_name))
			return ((long)error(fee->err, FATAL, NULL, NULL));
		gc_register(fee->err->gc, fee->err->cmd_name);
		if (!exec_cmd(token, fee->fd, fee->env, fee->err))
		{
			if (fee->fd->is_child)
			{
				if (fee->err->code == ERR_NO)
					print_err_msg(*(token->data), NULL, strerror(errno), fee->err->gc);
				else
					print_err_msg(*(token->data), NULL, fee->err->message[fee->err->code], fee->err->gc);
				gc_clean(fee->err->gc);
				exit(g_exit_status & 0x00FF);
			}
			return (FAILURE);
			waitpid(-1, NULL, 0);
		}
		if (!redir_destroy(IN, &(fee->fd->redirs), fee->err))
			return (FAILURE);
		if (!redir_destroy(OUT, &(fee->fd->redirs), fee->err))
			return (FAILURE);
		if (fee->fd->is_dad_pipe)
		{
			if (!pipe_destroy(fee->fd))
				return (FAILURE);
		}
		fee->fd->is_dad_pipe = 0;
	}
	return (SUCCESS);
}


/*
**	Return null if no error
*/

char	exec(t_btree *tree, t_list **env, t_err *err)
{
	t_fd			fd;
	t_fd_env_err	fee;

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
