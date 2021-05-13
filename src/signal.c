/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:04:10 by agautier          #+#    #+#             */
/*   Updated: 2021/05/11 15:03:466 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ctrl + \
*/

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

/*
**	Ctrl + C
**	TODO: clean tc buf
*/

static void	sigint(int signal)
{
	if (signal == SIGINT)	// TODO: == et pas !=
	{
		if (waitpid(-1, NULL, 0) == -1 && errno == ECHILD)
		{
			ft_putstr_fd("^C\n", STDOUT_FILENO);		// TODO: reactivate
			ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);	// TODO: Pose probleme des fois
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);		// TODO: reactivate
		g_exit_status = 128 + signal;
		g_exit_status |= 0x0100;
		// ft_putchar_fd('\n', STDIN_FILENO);
	}
}

/*
**
*/

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
