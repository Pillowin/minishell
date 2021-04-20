/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:46:45 by agautier          #+#    #+#             */
/*   Updated: 2021/04/20 19:52:50 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"
/*
**	Print strings in fd
*/

static int	is_flag(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (FAILURE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

unsigned char	builtin_echo(t_token *cmd, int fd, t_list **env)
{
	unsigned int	i;

	(void)env;
	i = 1;
	while (is_flag(cmd->data[i]))
		i++;
	while (cmd->data[i])
	{
		ft_putstr_fd(cmd->data[i], fd);
		i++;
		if (cmd->data[i])
			ft_putstr_fd(" ", fd);
	}
	if (!is_flag(cmd->data[1]))
		ft_putstr_fd("\n", fd);
	return (SUCCESS);
}
