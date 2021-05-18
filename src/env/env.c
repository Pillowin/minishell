/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:16:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 20:03:39 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create a list from main envp
*/

t_list	*env_init(char **envp, t_list **gc)
{
	unsigned int	i;
	t_list			*env;
	t_var			*var;
	t_var			v;
	t_list			*lst;
	char			*shlvl_value;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = var_init(get_var_name(envp[i], gc), get_var_equal(envp[i], gc), get_var_value(envp[i], gc), gc);	// TODO: verif
		if (!var)
			return (NULL);
		gc_list_push_back(&env, var, gc);
		i++;
	}
	lst = NULL;
	if (env)
		lst = ft_list_find(env, "SHLVL", &is_var);
	if (!env || !lst)
	{
		v = (t_var){"SHLVL", "=", "1"};
		tab_init(&(v.name), &(v.equal), &(v.value), gc);
		var = var_init(v.name, v.equal, v.value, gc);
		gc_list_push_back(&env, var, gc);
	}
	else
	{
		i = ft_atoi(((t_var *)lst->data)->value);
		i += 1;
		shlvl_value = ft_itoa(i);
		if (!shlvl_value)
			return (NULL);
		gc_register(gc, shlvl_value);
		if (!update_env(&env, "SHLVL", shlvl_value, gc))
			return (NULL);
	}
	return (env);
}

/*
**	list to tab
*/
char	**env_to_tab(t_list *env, t_list **gc)
{
	unsigned int	i;
	char			**envp;
	int				size;
	char			*tmp;

	size = ft_list_size(env);
	envp = (char **)gc_calloc(gc, size + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(((t_var *)env->data)->name, ((t_var *)env->data)->equal);
		if (!tmp)
			return (NULL);
		gc_register(gc, tmp);
		envp[i] = ft_strjoin(tmp, ((t_var *)env->data)->value);
		gc_free(gc, (void **)&tmp);
		if (!envp[i])
			return (NULL);
		gc_register(gc, envp[i]);
		env = env->next;
		i++;
	}
	return (envp);
}

/*
**
*/

t_list	*update_env(t_list **env, char *name, char *value, t_list **gc)
{
	t_list	*env_var;
	t_var	init;
	t_var	*var;


	env_var = ft_list_find(*env, name, &is_var);
	if (!env_var || !(((t_var *)env_var->data)->value))
	{
		init.name = name;
		init.equal = "=";		// TODO: leak name ?
		// if (env_var && ((t_var *)env_var->data)->name)
		// 	init.name = ((t_var *)env_var->data)->name;
		// if (env_var && ((t_var *)env_var->data)->equal)
		// 	init.equal = ((t_var *)env_var->data)->equal;
		init.value = value;

		if (!tab_init(&(init.name), &(init.equal), &(init.value), gc))
			return (NULL);
		var = var_init(init.name, init.equal, init.value, gc);
		if (!var)
			return (NULL);
		gc_list_push_back(env, var, gc);
		return(ft_lstlast(*env));
	}
	gc_free(gc, (void **)&((t_var *)env_var->data)->value);
	((t_var *)env_var->data)->value = value;
	return (env_var);
}

/*
**
*/

t_list	*insert_env(t_list **env, t_var v, t_list **gc)
{
	t_var	*var;
	
	var = var_init(v.name, v.equal, v.value, gc);
	if (!var)
		return (NULL);
	gc_list_push_back(env, var, gc);
	return(ft_lstlast(*env));
}
