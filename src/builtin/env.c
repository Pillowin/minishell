/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:13:10 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 15:41:54 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Print environnement variables.
*/
char	builtin_env(t_token *cmd, t_list **env, t_err *err)
{
	t_list	*curr;

	if (cmd->data[1])
	{
		perr_msg("env", cmd->data[1], err->message[NO_SUCH_FILE], err->gc);
		g_exit_status = 127;
		return ((long)error(err, NONE, NULL, NULL));
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
