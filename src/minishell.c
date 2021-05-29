/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:25:50 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/29 11:52:27 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
static char	minishell_init(t_tc_cmds **tc_cmds, t_err *err)
{
	*tc_cmds = tc_cmds_init(err->gc);
	if (!(*tc_cmds))
	{
		perr_msg(NULL, NULL, strerror(errno), err->gc);
		gc_clean(err->gc);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}

/*
**
*/
static char	minishell_start(char *buf, int len, t_list **env, t_err *err)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (!buf || !(*buf))
		return (SUCCESS);
	buf[len] = '\n';
	if (!(lexer(buf, err, env)))
	{
		if (err->code == ERR_NO || err->code == FATAL)
			perr_msg(err->cmd_name, NULL, strerror(errno), err->gc);
		else if (err->code != NONE)
			perr_msg(err->cmd_name, NULL, err->message[err->code], err->gc);
		if (err->code == FATAL)
			return (FAILURE);
	}
	waitall();
	return (SUCCESS);
}

/*
**
*/
void	minishell(t_list **env, t_err *err)
{
	t_tc_cmds	*tc_cmds;
	char		*buf;
	int			len;

	tc_cmds = NULL;
	minishell_init(&tc_cmds, err);
	buf = NULL;
	while (1)
	{
		ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);
		gc_free(err->gc, (void **)&(err->cmd_name));
		gc_free(err->gc, (void **)&buf);
		len = tc_read(tc_cmds, &buf, err->gc);
		if (len == CTRL_D)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		else if (len == ERRNO_ERR)
			perr_msg("\n", NULL, strerror(errno), err->gc);
		else if (!minishell_start(buf, len, env, err))
			break ;
	}
}
