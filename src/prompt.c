/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 01:18:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 22:110:00 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
**	Print pretty prompt and set PS1if needed.
*/

char	prompt(t_list **env)
{
	t_list	*prompt;

	prompt = ft_list_find(*env, (void *)"PS1", &is_var);
	if (!prompt || !((((t_var *)prompt->data)->value)))
		prompt = update_env(env, "PS1", DEFAULT_PROMPT);
	// printf("%d ", g_exit_status & 0x00FF);	fflush(stdout);	// TODO: REMOVE 
	ft_putstr_fd(((t_var *)prompt->data)->value, STDOUT_FILENO);
	return (SUCCESS);
}
