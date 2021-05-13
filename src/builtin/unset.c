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

// /*
// **
// */
// static int	cmp(void *data, void *ref)
// {
// 	if (!ft_strcmp(((t_var *)data)->name, ref))
// 		return (0);
// 	return (1);
// }

/*
**	
*/
unsigned char	builtin_unset(t_token *cmd, t_list **env, t_err *err)
{
	unsigned int	i;
	t_var			*var;
	int				tmp;

	(void)err;
	i = 1;
	if (!(cmd->data[i]))
		return (SUCCESS);
	while (cmd->data[i])
	{
		if (!is_name(cmd->data[i], '='))
		{
			tmp = dup(STDOUT_FILENO);
			dup2(STDERR_FILENO, STDOUT_FILENO);			// TODO: message pour cd et export avec les « toto+toto=tonton »
			printf("minishell: :%s: « %s » : %s\n", cmd->data[0], cmd->data[1], err->message[EXPORT]);
			dup2(tmp, STDOUT_FILENO);
			i++;
			continue ;
		}
		var = var_init(NULL, NULL, NULL, err->gc);
		if (!var)
			return (FAILURE);
		var->name = get_var_name(cmd->data[i], err->gc);
		if (!(var->name))
		{
			var_destroy(var, err->gc);
			return (FAILURE);
		}
		gc_list_remove_var(env, (void *)var->name, err->gc);
		var_destroy(var, err->gc);
		i++;
	}
	return (SUCCESS);
}
