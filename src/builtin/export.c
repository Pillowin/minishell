/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiutier <agiatier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:26:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 16:111:12 by atgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

static int	cmp(void *data, void *ref)
{
	if (!data || !ref || !(((t_var *)data)->name) || !(((t_var *)ref)->name))
		return (FAILURE);
	return (ft_strcmp(((t_var *)data)->name, ((t_var *)ref)->name));
}

/*
**	Add new var to envp
**	TODO: verif var name
*/

static t_list	*lstdup(t_list *lst, t_list **gc)
{
	t_list	*begin;

	begin = NULL;
	while (lst)
	{
		gc_list_push_back(&begin, lst->data, gc);
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
	if (*((t_var *)data)->equal)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		if (((t_var *)data)->value)
			ft_putstr_fd(((t_var *)data)->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/*
** cmd[0] = export
** cmd[1] = name=value
*/

unsigned char	builtin_export(t_token *cmd, t_list **env, t_err *err)
{
	unsigned int	i;
	t_list			*list;
	t_var			*var;
	t_list			*env_tmp;

	i = 1;
	if (!(cmd->data[i]))	// si juste export
	{
		env_tmp = lstdup(*env, err->gc);
		ft_list_sort(env, &cmp);
		ft_list_foreach(env_tmp, &print_env);
		gc_list_clear(env_tmp, err->gc);
		return (SUCCESS);
	}
	while (cmd->data[i])	// s'il y a des arguments
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
		list = ft_list_find(*env, var, &cmp);
		var_destroy(var, err->gc);
		if (!list)
		{
			var->name = get_var_name(cmd->data[i], err->gc);
			if (!var->name)
				return ((long)error(err, FATAL, NULL, NULL));
			var->equal = get_var_equal(cmd->data[i], err->gc);
			if (!var->equal)
				return ((long)error(err, FATAL, NULL, NULL));
			var->value = get_var_value(cmd->data[i], err->gc);
			if (!var->value)
				return ((long)error(err, FATAL, NULL, NULL));
			if (!insert_env(env, *var, err->gc))
				return ((long)error(err, FATAL, NULL, NULL));
			var_destroy(var, err->gc);
		}
		else
		{
			var->value = get_var_value(cmd->data[i], err->gc);
			if (!var->value)
				return ((long)error(err, FATAL, NULL, NULL));
			if (!update_env(env, ((t_var *)list->data)->name, var->value, err->gc))
				return ((long)error(err, FATAL, NULL, NULL));
			gc_free(err->gc, (void **)&(var->value));
		}
		i++;
	}
	return (SUCCESS);
}
