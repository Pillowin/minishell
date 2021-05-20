/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:41:12 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 17:23:20 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Remove a variable from environment.
*/
char	builtin_unset(t_token *cmd, t_list **env, t_err *err)
{
	unsigned int	i;
	t_var			*var;

	i = 1;
	if (!(cmd->data[i]))
		return (SUCCESS);
	while (cmd->data[i])
	{
		if (!is_name(cmd->data[i], '='))
		{
			perr_msg(cmd->data[0], cmd->data[1], err->message[EXPORT], err->gc);
			i++;
			continue ;
		}
		var = var_init(cmd->data[i], err->gc);
		if (!var)
			return ((long)error(err, FATAL, NULL, NULL));
		gc_list_remove_var(env, var->name, err->gc);
		var_destroy(var, err->gc);
		i++;
	}
	return (SUCCESS);
}
