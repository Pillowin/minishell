/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:17:06 by agautier          #+#    #+#             */
/*   Updated: 2021/05/28 19:08:29 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if str is a valid parameter for exit builtin.
*/
static	char	is_valid_arg(char *str)
{
	unsigned int	i;

	i = 0;
	if ((str[i] < '0' && str[i] != '-' && str[i] != '+') || str[i] > '9')
		return (FAILURE);
	i = 1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
**	Quit minishell and return first numeric arg if supplied or last exit status.
*/
char	builtin_exit(t_token *cmd, t_list **env, t_err *err)
{
	(void)env;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->data[1])
	{
		if (!is_valid_arg(cmd->data[1]))
		{
			perr_msg("exit", cmd->data[1], "numeric argument required",
				err->gc);
			g_exit_status = 2;
		}
		else if (cmd->data[1] && cmd->data[2])
		{
			perr_msg("minishell", "exit", "too many arguments", err->gc);
			g_exit_status = EXIT_FAILURE;
			return (FAILURE);
		}
		else
			g_exit_status = ft_atoi(cmd->data[1]);
	}
	gc_clean(err->gc);
	exit(g_exit_status & 0x00FF);
	return (SUCCESS);
}
