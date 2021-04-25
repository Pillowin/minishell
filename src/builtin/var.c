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

t_var	*var_init(char *name, char *equal, char *value)
{
	t_var	*var;

	var = (t_var *)ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	var->name = name;
	var->equal = equal;
	var->value = value;
	return (var);
}

void	var_destroy(void *data)
{
	t_var	*var;

	if (!data)
		return ;
	var = (t_var *)data;
	ft_free((void **)&(var->name));
	ft_free((void **)&(var->equal));
	ft_free((void **)&(var->value));
	ft_free((void **)&(var));
}

/*
**
*/
char	*get_var_name(char *var)
{
	unsigned int	i;
	char			*value;
	char			*name;

	value = ft_strchr(var, '=');
	if (value)
	{
		i = value - var + 1;
		name = ft_substr(var, 0, i - 1);
		if (!name)
			return (NULL);
	}
	else
	{
		name = ft_strdup(var);
		if (!name)
			return (NULL);
	}
	return (name);
}

char	*get_var_equal(char *var)
{
	char	*equal;

	equal = NULL;
	if (ft_strchr(var, '='))
	{
		equal = ft_strdup("=");
		if (!equal)
			return (FAILURE);
	}
	else
	{
		equal = ft_strdup("");
		if (!equal)
			return (FAILURE);
	}
	return (equal);
}

/*
**	
*/
char	*get_var_value(char *var)
{
	unsigned int	i;
	char			*value;

	value = ft_strchr(var, '=');
	if (value)
	{
		i = value - var + 1;
		value = ft_substr(var, i, ft_strlen(var) - i);
		if (!value)
			return (FAILURE);
	}
	else
	{
		value = ft_strdup("");
		if (!value)
			return (FAILURE);
	}
	return (value);
}
