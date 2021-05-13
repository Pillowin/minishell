/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:16:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 20:27:09 by agautier         ###   ########.fr       */
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

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = var_init(get_var_name(envp[i], gc), get_var_equal(envp[i], gc), get_var_value(envp[i], gc), gc);
		if (!var)
			return (NULL);
		gc_list_push_back(&env, var, gc);
		i++;
	}
	return (env);
}

/*
**	list to tab
*/
char	**env_to_tab(t_list *env)
{
	unsigned int	i;
	char			**envp;
	int				size;
	char			*tmp;

	size = ft_list_size(env);
	envp = (char **)ft_calloc(size + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(((t_var *)env->data)->name, ((t_var *)env->data)->equal);
		if (!tmp)
		{
			ft_free_tab((void **)tmp);
			return (NULL);	// TODO: err malloc
		}
		envp[i] = ft_strjoin(tmp, ((t_var *)env->data)->value);
		ft_free((void **)&tmp);
		if (!envp[i])
		{
			ft_free_tab((void **)envp);
			return (NULL);	// TODO: err malloc
		}
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

	env_var = ft_list_find(*env, (void *)name, &is_var);
	if (!env_var || !((t_var *)env_var->data)->value)
	{
		init.name = name;
		init.equal = "=";
		if (env_var && ((t_var *)env_var->data)->name)
			init.name = ((t_var *)env_var->data)->name;
		if (env_var && ((t_var *)env_var->data)->equal)
			init.equal = ((t_var *)env_var->data)->equal;
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
	ft_list_push_back(env, var);
	return(ft_lstlast(*env));
}
