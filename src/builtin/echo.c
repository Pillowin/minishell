/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:46:45 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 00:09:38 by agautier         ###   ########.fr       */
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

unsigned char	builtin_echo(t_token *cmd, t_list **env)
{
	unsigned int	i;

	(void)env;
	i = 1;
	while (is_flag(cmd->data[i]))
		i++;
	while (cmd->data[i])
	{
		printf("%s", cmd->data[i]);
		i++;
		if (cmd->data[i])
			printf(" ");
	}
	if (!is_flag(cmd->data[1]))
		printf("\n");
	return (SUCCESS);
}
