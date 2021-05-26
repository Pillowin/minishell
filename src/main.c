/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:36:46 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 18:31:17 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/
int	main(int argc, char **argv, char **envp)
{
	char	*err_msg[ERR_NO];
	t_err	err;
	t_list	*env;
	t_list	*gc;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	err_init(err_msg);
	gc = NULL;
	err = (t_err){&gc, err_msg, 0, NULL};
	env = env_init(envp, err.gc);
	if (!env)
	{
		perr_msg(NULL, NULL, strerror(errno), err.gc);
		gc_clean(err.gc);
		exit(EXIT_FAILURE);
	}
	signal_init(err.gc);
	minishell(&env, &err);
	gc_clean(err.gc);
	return (g_exit_status);
}
