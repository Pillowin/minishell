/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 22:00:53 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 22:01:03 by agautier         ###   ########.fr       */
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
			if (WIFSIGNALED(stat_loc))
				g_exit_status = WEXITSTATUS(stat_loc);
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			g_exit_status = 128 + signal;
			g_exit_status |= 0x1000;
		}
	}
}

/*
**	Ctrl + C
*/
static void	sigint(int signal)
{
	if (signal == SIGINT)
	{
		if (waitpid(-1, NULL, 0) == -1 && errno == ECHILD)
		{
			ft_putstr_fd("^C\n", STDOUT_FILENO);
			ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 128 + signal;
		g_exit_status |= 0x0100;
	}
}

/*
**
*/
void	signal_init(t_list **gc)
{
	if (signal(SIGINT, &sigint) == SIG_ERR)
	{
		perr_msg(NULL, NULL, strerror(errno), gc);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, &sigquit) == SIG_ERR)
	{
		perr_msg(NULL, NULL, strerror(errno), gc);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
}
