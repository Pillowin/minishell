/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:03:32 by agautier          #+#    #+#             */
/*   Updated: 2021/05/09 17:26:59 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

void	minishell(t_list *env, t_err *err)
{
	t_dlist	*cmds;
	t_dlist	*cpy;
	t_dlist	*tmp;
	char	*buf;
	int		len;

	buf = NULL;
	cmds = NULL;
	cpy = NULL;
	while (1)
	{
		if (!prompt(&env))
		{
			ft_list_foreach(env, &var_destroy);
			ft_list_clear(env, &ft_free);
			break ;	// TODO: use error
		}

		ft_free((void **)&buf);
		len = tc_read(&cmds, &cpy, &buf, &env);
		// printf("\ncmd=`%s`\tlast exit_status=`%d`\n", buf, g_exit_status);
		if (len == -1)
		{
			ft_putstr_fd("\nexit\n", STDOUT_FILENO);
			break ;
		}
		else if (len == -2)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		else
		{
			// if (buf[len - 1] != '\n')
			ft_putchar_fd('\n', STDOUT_FILENO);
			buf[len] = '\n';
			if(!(lexer(buf, err, env)))
			{
				ft_putendl_fd(err->message[err->code], STDERR_FILENO);	// TODO: etait utile ?
				// printf("erreur dans minishell\n");
				// return (EXIT_FAILURE);
				// continue ;
			}
		}
	}
	
	ft_free((void **)&buf);
	while (cmds)
	{
		ft_free((void **)&(cmds->data));
		tmp = cmds;
		cmds = cmds->next;
		ft_free((void **)&tmp);
	}
	while (cpy)
	{
		ft_free((void **)&(cpy->data));
		tmp = cpy;
		cpy = cpy->next;
		ft_free((void **)&tmp);
	}
}
