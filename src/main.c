/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaetier <agaeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:48:27 by agautier          #+#    #+#             */
/*   Updated: 2021/03/31 16:22:29by a ggeutee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: enter sans char exit

/*
**
*/
void	minishell(t_list *env, t_err *err)
{
	t_dlist			*cmds;
	t_dlist			*cpy;
	char			*buf;
	int			len;

	cmds = NULL;
	cpy = NULL;
	while (1)
	{
		if (!prompt(&env))
		{
			ft_list_foreach(env, &var_destroy);
			ft_list_clear(env, &ft_free);
			return ;	// TODO: use error
		}

		buf = NULL;
		len = tc_read(&cmds, &cpy, &buf, &env);
		printf("\ncmd=`%s`\tlast exit_status=`%d`\n", buf, g_exit_status);
		if (len == -1)
		{
			ft_putstr_fd("\nexit\n", STDOUT_FILENO);
			return ;
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
				ft_putendl_fd(err->message[err->code], STDERR_FILENO);
				// printf("erreur dans minishell\n");
				// return (EXIT_FAILURE);
				// continue ;
			}
		}
	}
}

/*
**	
*/
int	main(int argc, char **argv, char **envp)
{
	char 	*err_msg[15];	// TODO:
	t_err	err;
	t_list	*env;

	(void)argc;
	(void)argv;

	g_exit_status = 0;
	err_init(err_msg);
	err = (t_err){err_msg, 0, NULL};

	env = env_init(envp);
	if (!env)
	{
		ft_list_foreach(env, &var_destroy);
		ft_list_clear(env, &ft_free);
		return (EXIT_FAILURE);	// TODO: use error
	}
	
	signal_init();
	minishell(env, &err);
	ft_list_foreach(env, &var_destroy);
	ft_list_clear(env, &ft_free);
	return (g_exit_status);
}
