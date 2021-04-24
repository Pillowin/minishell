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

unsigned char	builtin_env(t_token *cmd, t_list **env)
{
	if (cmd->data[1])
		return (FAILURE);
	while (*env)
	{
		if (((t_var *)((*env)->data))->value)
			printf("%s=%s\n", ((t_var *)((*env)->data))->name,
					((t_var *)((*env)->data))->value);
		*env = (*env)->next;
	}
	return (SUCCESS);
}
