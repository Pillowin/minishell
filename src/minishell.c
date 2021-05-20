/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgqetier <mgqitgerstudent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:03:32 by agautier          #+#    #+#             */
/*   Updated: 2021/05/10 17:31:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

void	minishell(t_list **env, t_err *err)
{
	t_tc_cmds	*tc_cmds;
	char		*buf;
	int			len;

	buf = NULL;
	tc_cmds = tc_cmds_init(err->gc);
	if (!tc_cmds)
	{
		perr_msg(NULL, NULL, strerror(errno), err->gc);
		gc_clean(err->gc);
		exit(EXIT_FAILURE);
	}
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
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			perr_msg(NULL, NULL, strerror(errno), err->gc);
		}
		else
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			if (!buf || !(*buf))
				continue ;
			buf[len] = '\n';
			if(!(lexer(buf, err, env)))	// SI ERR_NO && errno == ERR malloc gc_clean ;exit
			{
				if (err->code == ERR_NO || err->code == FATAL)
					perr_msg(err->cmd_name, NULL, strerror(errno), err->gc);
				else if (err->code != NONE)
					perr_msg(err->cmd_name, NULL, err->message[err->code], err->gc);
				if (err->code == FATAL)
					break ;
				// ft_putendl_fd(err->message[err->code], STDERR_FILENO);	// TODO: ?! pas de minishell: ?
			}
		}
		waitall();
	}
	gc_clean(err->gc);	// TODO: activate
}
