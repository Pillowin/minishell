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
static int	cmp(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}

/*
**	
*/
unsigned char	builtin_unset(t_token *cmd, int fd, t_list **env)
{
	unsigned int	i;
	t_var			*var;

	(void)fd;
	i = 1;
	if (!(cmd->data[i]))
		return (FAILURE);
	while (cmd->data[i])
	{
		var = var_init(get_name(cmd->data[i]), NULL, NULL);
		ft_list_remove_if(env, (void *)var->name, &cmp, &var_destroy);
		var_destroy(var);
		i++;
	}
	return (SUCCESS);
}
