/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:25:48 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 18:25:55 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
t_var	*var_init(char *str, t_list **gc)
{
	t_var	*var;

	var = (t_var *)gc_calloc(gc, 1, sizeof(*var));
	if (!var)
		return (NULL);
	var->name = var_get_name(str, gc);
	if (!var->name)
		return (NULL);
	var->equal = var_get_equal(str, gc);
	if (!var->equal)
		return (NULL);
	var->value = var_get_value(str, gc);
	if (!var->value)
		return (NULL);
	return (var);
}

/*
**
*/
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
char	*var_get_name(char *var, t_list **gc)
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

/*
**
*/
char	*var_get_equal(char *var, t_list **gc)
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
char	*var_get_value(char *var, t_list **gc)
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
