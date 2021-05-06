/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:04:10 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 11:47:19 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigquit(int signal)
{
	int	stat_loc;

	if (signal == SIGQUIT)
	{
		if (waitpid(-1, &stat_loc, 0) != -1)
		{
			// printf("es = %d\n", g_exit_status);
			if (WIFSIGNALED(stat_loc))
			{
			// printf("es = %d\n", g_exit_status);
				g_exit_status = WEXITSTATUS(stat_loc);
			}
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			// printf("es = %d\n", g_exit_status);
			g_exit_status = 128 + signal;	// TODO:
			// printf("es = %d\n", g_exit_status);
		}
	}
}

static void	sigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (waitpid(-1, NULL, 0) == -1 && errno == ECHILD)
			ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);
		g_exit_status = 128 + signal;	// TODO:
	}
}

void	signal_init()
{
	if (signal(SIGINT, &sigint) == SIG_ERR)
	{
		// TODO: error
		printf("err signal\n");
	}
	if (signal(SIGQUIT, &sigquit) == SIG_ERR)
	{
		// TODO: error
		printf("err signal\n");
	}
}
