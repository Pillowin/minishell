/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:56:59 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 19:02:5 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_init(char *name, char *equal, char *value, t_list **gc)
{
	t_var	*var;

	var = (t_var *)gc_calloc(gc, 1, sizeof(*var));
	if (!var)
		return (NULL);
	var->name = name;
	var->equal = equal;
	var->value = value;
	return (var);
}

void	var_destroy(void *data, t_list **gc)
{
	t_var	*var;

	if (!data)
		return ;
	var = (t_var *)data;
	gc_free(gc, (void **)&(var->name));
	gc_free(gc, (void **)&(var->equal));
	gc_free(gc, (void **)&(var->value));
	gc_free(gc, (void **)&(var));
}

/*
**
*/
char	*get_var_name(char *var, t_list **gc)
{
	unsigned int	i;
	char			*value;
	char			*name;


	value = ft_strchr(var, '=');
	if (value)
	{
		i = value - var + 1;
		name = ft_substr(var, 0, i - 1);
	}
	else
		name = ft_strdup(var);
	if (!name)
		return (NULL);
	gc_register(gc, name);
	return (name);
}

char	*get_var_equal(char *var, t_list **gc)
{
	char	*equal;

	equal = NULL;
	if (ft_strchr(var, '='))
		equal = ft_strdup("=");
	else
		equal = ft_strdup("");
	if (!equal)
		return (NULL);
	gc_register(gc, equal);
	return (equal);
}

/*
**	
*/
char	*get_var_value(char *var, t_list **gc)
{
	unsigned int	i;
	char			*value;

	value = ft_strchr(var, '=');
	if (value)
	{
		i = value - var + 1;
		value = ft_substr(var, i, ft_strlen(var) - i);
	}
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	gc_register(gc, value);
	return (value);
}
