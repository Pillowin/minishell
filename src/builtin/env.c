/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:59:17 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 19:19:341 byagattierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	builtin_env(t_token *cmd, int fd, t_list **env)
{
	if (cmd->data[1])
		return (FAILURE);
	while (*env)
	{
		if (((t_var *)((*env)->data))->value)
		{
			ft_putstr_fd(((t_var *)((*env)->data))->name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(((t_var *)((*env)->data))->value, fd);
		}
		*env = (*env)->next;
	}
	return (SUCCESS);
}
