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

void	minishell(t_list *env, t_err *err)
{
	t_tc_cmds	*tc_cmds;
	char		*buf;
	int			len;

	buf = NULL;
	tc_cmds = tc_cmds_init(err->gc);
	if (!tc_cmds)
	{
		gc_clean(err->gc);
		return ;	// TODO: err malloc
	}
	while (1)
	{
		prompt();
		gc_free(err->gc, (void **)&buf);
		len = tc_read(tc_cmds, &buf, err->gc);
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (len == CTRL_D)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		else if (len == ERRNO_ERR)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);	// TODO:	err print func
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		else
		{
			if (!buf || !(*buf))
				continue ;
			buf[len] = '\n';
			if(!(lexer(buf, err, env)))
				ft_putendl_fd(err->message[err->code], STDERR_FILENO);
		}
		waitall();
	}
	
	// ft_free((void **)&buf);
	gc_clean(err->gc);
}
