/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:30:05 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 21:555:166 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	
*/
unsigned char	builtin_unset(t_token *cmd, t_list **env, t_err *err)
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
			print_err_msg(cmd->data[0], cmd->data[1], err->message[EXPORT], err->gc);
			i++;
			continue ;
		}
		var = var_init(NULL, NULL, NULL, err->gc);
		if (!var)
			return ((long)error(err, FATAL, NULL, NULL));
		var->name = get_var_name(cmd->data[i], err->gc);
		if (!(var->name))
			return ((long)error(err, FATAL, NULL, NULL));
		gc_list_remove_var(env, (void *)var->name, err->gc);
		var_destroy(var, err->gc);
		i++;
	}
	return (SUCCESS);
}
