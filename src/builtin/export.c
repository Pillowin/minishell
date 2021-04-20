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
**	ft_lst_foreach with 2 parameter in f
*/

static void	ft_list_foreach_fd(t_list *begin, int fd, void (*f)(void *, int))
{
	while (begin)
	{
		(*f)(begin->data, fd);
		begin = begin->next;
	}
}

/*
**	
*/
static void	print_env(void *data, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(((t_var *)data)->name, fd);
	if (((t_var *)data)->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(((t_var *)data)->value, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

/*
**	
*/
static char	check_syntax(char *name)
{
	unsigned int	i;

	if (!name)
		return (FAILURE);
	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (FAILURE);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
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
unsigned char	builtin_export(t_token *cmd, int fd, t_list **env)
{
	unsigned int	i;
	t_list			*lst;
	t_var			*var;
	t_var			*new;

	i = 1;
	if (!cmd->data[i])
	{
		*env = lstdup(*env);
		ft_list_sort(env, &ft_strcmp);
		ft_list_foreach_fd(*env, fd, &print_env);
		ft_list_clear(*env, &ft_free);
		return (SUCCESS);
	}
	while (cmd->data[i])
	{
		var = var_init(NULL, NULL, NULL);
		if (!var)
			return (FAILURE);
		var->name = get_name(cmd->data[i]);
		if (!check_syntax(var->name))
		{
			var_destroy(var);
			return (FAILURE);	// TODO: identifiant non valable
		}
		lst = is_created(*env, var->name);
		if (lst)
		{
			ft_free((void **)&((t_var *)lst->data)->value);
			((t_var *)lst->data)->value = get_value(cmd->data[i]);
			if (!(((t_var *)lst->data)->value))
			{
				ft_free((void **)&(var->name));
				return (FAILURE);
			}
		}
		else
		{
			new = var_init(get_name(cmd->data[i]), get_equal(cmd->data[i]), get_value(cmd->data[i]));
			if (!new)
				return (FAILURE);
			ft_list_push_back(env, new);
		}
		i++;
		var_destroy(var);
	}
	return (SUCCESS);
}
