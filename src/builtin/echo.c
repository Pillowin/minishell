/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:46:45 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 14:42:53 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if str is flag -n.
*/
static int	is_flag(char *str)
{
	int	i;

	if (!str)
		return (FAILURE);
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

/*
**	Print strings in fd.
*/
char	builtin_echo(t_token *cmd, t_list **env, t_err *err)
{
	unsigned int	i;

	(void)err;
	(void)env;
	i = 1;
	while (is_flag(cmd->data[i]))
		i++;
	while (cmd->data[i])
	{
		ft_putstr_fd(cmd->data[i], STDOUT_FILENO);
		i++;
		if (cmd->data[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_flag(cmd->data[1]))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
