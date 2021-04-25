/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:26:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 16:111:12 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Add new var to envp
**	TODO: verif var name
*/

static t_list	*lstdup(t_list *lst)
{
	t_list	*begin;

	begin = NULL;
	while (lst)
	{
		ft_list_push_back(&begin, lst->data);
		lst = lst->next;
	}
	return (begin);
}


/*
**	
*/
static void	print_env(void *data)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(((t_var *)data)->name, STDOUT_FILENO);
	if (((t_var *)data)->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(((t_var *)data)->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}



/*
**	Check if list already contains a var with name
*/
static	t_list	*is_created(t_list *env, char *name)
{
	if (!name)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->data)->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
** cmd[0] = export
** cmd[1] = name=value
*/
unsigned char	builtin_export(t_token *cmd, t_list **env)
{
	unsigned int	i;
	t_list			*lst;
	t_var			*var;
	t_var			*new;

	i = 1;
	if (!(cmd->data[i]))	// si juste export
	{
		*env = lstdup(*env);
		ft_list_sort(env, &ft_strcmp);
		ft_list_foreach(*env, &print_env);
		ft_list_clear(*env, &ft_free);
		return (SUCCESS);
	}
	while (cmd->data[i])	// s'il y a des arguments
	{
		var = var_init(NULL, NULL, NULL);
		if (!var)
			return (FAILURE);
		var->name = get_var_name(cmd->data[i]);	// TODO: use same func as expand_dollar ?
		if (!is_name(var->name, '='))
		{
			var_destroy(var);
			return (FAILURE);	// TODO: identifiant non valable
		}
		lst = is_created(*env, var->name);
		if (lst)	// si la var etait deja dans la liste
		{
			ft_free((void **)&((t_var *)lst->data)->value);
			((t_var *)lst->data)->value = get_var_value(cmd->data[i]);
			if (!(((t_var *)lst->data)->value))
			{
				ft_free((void **)&(var->name));
				return (FAILURE);
			}
		}
		else	// si la var existe pas
		{
			new = var_init(get_var_name(cmd->data[i]), get_var_equal(cmd->data[i]), get_var_value(cmd->data[i]));
			if (!new)
				return (FAILURE);
			ft_list_push_back(env, new);
		}
		i++;
		var_destroy(var);
	}
	return (SUCCESS);
}
