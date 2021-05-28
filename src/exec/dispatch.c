/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:29:38 by agautier          #+#    #+#             */
/*   Updated: 2021/05/28 18:57:42 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Init pipe.
*/
static char	dispatch_pipe(t_fd *fd, t_err *err)
{
	if (!pipe_init(fd))
		return ((long)error(err, ERR_NO, NULL, NULL));
	fd->is_dad_pipe = 1;
	return (SUCCESS);
}

/*
**	Print error message then exit cleanly.
*/
static void	exit_err(char *cmd_name, t_err *err)
{
	if (err->code == ERR_NO)
		perr_msg(cmd_name, NULL, strerror(errno), err->gc);
	else
		perr_msg(cmd_name, NULL, err->message[err->code], err->gc);
	gc_clean(err->gc);
	exit(g_exit_status & 0x00FF);
}

/*
**	Init redir.
*/
static char	dispatch_redir(t_token *token, t_fd *fd, t_err *err)
{
	if (!redir_init(token, &(fd->redirs), err))
	{
		if (!redir_destroy(IN, &(fd->redirs), err))
			return (FAILURE);
		if (!redir_destroy(OUT, &(fd->redirs), err))
			return (FAILURE);
		if (fd->is_child)
			exit_err(err->cmd_name, err);
		return (FAILURE);
	}
	fd->is_dad_pipe = 0;
	return (SUCCESS);
}

/*
**	type == TOKEN_COMMAND
**	Execute command.
*/
static char	dispatch_command(t_token *token, t_fd *fd, t_list **env, t_err *err)
{
	if (fd->pipes[REAL_IN] == -1 && fd->pipes[REAL_OUT] == -1)
		waitpid(-1, NULL, 0);
	err->cmd_name = gc_strdup(token->data[0], err->gc);
	if (!(err->cmd_name))
		return ((long)error(err, FATAL, NULL, NULL));
	if (!exec_cmd(token, fd, env, err))
	{
		if (fd->is_child)
			exit_err(*(token->data), err);
		return (FAILURE);
		waitpid(-1, NULL, 0);
	}
	if (!redir_destroy(IN, &(fd->redirs), err))
		return (FAILURE);
	if (!redir_destroy(OUT, &(fd->redirs), err))
		return (FAILURE);
	if (fd->is_dad_pipe)
		if (!pipe_destroy(fd))
			return (FAILURE);
	if (!(g_exit_status & 0xFF00))
		g_exit_status &= 0x00FF;
	fd->is_dad_pipe = 0;
	return (SUCCESS);
}

/*
**	Dispatch to corresponding function depending of token type.
*/
char	dispatch(void *item, t_fd_env_err *fee)
{
	t_token	*token;

	token = (t_token *)item;
	if (token->type == TOK_PIPE)
	{
		if (!dispatch_pipe(fee->fd, fee->err))
			return (FAILURE);
	}
	else if (token->type == TOK_REDIR)
	{
		if (!dispatch_redir(token, fee->fd, fee->err))
			return (FAILURE);
	}
	else if (token->type == TOK_COMMAND)
	{
		if (!dispatch_command(token, fee->fd, fee->env, fee->err))
			return (FAILURE);
	}
	return (SUCCESS);
}
