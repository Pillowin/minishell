/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:48:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 16:19:08 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


const char* __asan_default_options() { return "detect_leaks=0"; }	// TODO: hide fsanitize leaks

/*
**	
*/

int	main(int argc, char **argv, char **envp)
{
	char 	*err_msg[ERR_NO];	// TODO:
	t_err	err;
	t_list	*env;

	(void)argc;
	(void)argv;

	g_exit_status = 0;
	err_init(err_msg);
	err = (t_err){NULL, err_msg, 0, NULL};

	env = env_init(envp);
	if (!env)
	{
		ft_list_foreach(env, &var_destroy);
		ft_list_clear(env, &ft_free);
		// fprintf(stderr, "err env\n");
		// return (EXIT_FAILURE);	// TODO: use error
	}
	
	signal_init();
	minishell(env, &err);
	ft_list_foreach(env, &var_destroy);
	ft_list_clear(env, &ft_free);
	return (g_exit_status);
}
