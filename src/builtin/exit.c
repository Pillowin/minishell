/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:01:31 by agautier          #+#    #+#             */
/*   Updated: 2021/05/19 14:07:29 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
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
**
*/

unsigned char	builtin_exit(t_token *cmd, t_list **env, t_err *err)
{
	// TODO: pas toujours ecrire exit - pas toujours exit en fonction du nombre d'argument / type d'arg
	(void)env;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->data[1] && cmd->data[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = EXIT_FAILURE;
	}
	else if (cmd->data[1])
	{
		g_exit_status = 2;
		if (!is_valid_arg(cmd->data[1]))
			print_err_msg("exit", cmd->data[1], "numeric argument required", err->gc);
		else
			g_exit_status = ft_atoi(cmd->data[1]);
	}
	gc_clean(err->gc);
	exit(g_exit_status & 0x00FF);
	return (SUCCESS);
}
