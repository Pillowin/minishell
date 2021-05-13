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
	if (((t_var *)data)->equal)
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
	int				tmp;
	t_list			*list;
	t_var			*var;

	i = 1;
	if (!(cmd->data[i]))	// si juste export
	{
		*env = lstdup(*env);
		ft_list_sort(env, &cmp);
		ft_list_foreach(*env, &print_env);
		ft_list_clear(*env, &ft_free);
		return (SUCCESS);
	}
	while (cmd->data[i])	// s'il y a des arguments
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
		list = ft_list_find(*env, var, &cmp);
		if (!list)
			insert_env(env, (t_var){get_var_name(cmd->data[i], err->gc), get_var_equal(cmd->data[i], err->gc), get_var_value(cmd->data[i], err->gc)}, err->gc);
		else
			update_env(env, ((t_var *)list->data)->name, get_var_value(cmd->data[i], err->gc), err->gc);
		var_destroy(var, err->gc);
		i++;
	}
	return (SUCCESS);
}
