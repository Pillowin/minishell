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

/*
**	
*/

unsigned char	builtin_env(t_token *cmd, t_list **env, t_err *err)
{
	t_list	*curr;

	if (cmd->data[1])
	{
		g_exit_status = 127;
		print_err_msg("env", cmd->data[1], "No such file or directory", err->gc);
		return (SUCCESS);
	}
	curr = *env;
	while (curr)
	{
		if (*(((t_var *)(curr->data))->equal))
		{
			ft_putstr_fd(((t_var *)(curr->data))->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			if (*(((t_var *)(curr->data))->value))
				ft_putstr_fd(((t_var *)(curr->data))->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}	
		curr = curr->next;
	}
	return (SUCCESS);
}
