/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:48:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 22:33:11 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
