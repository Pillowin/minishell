/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:18:33 by agautier          #+#    #+#             */
/*   Updated: 2021/05/29 12:10:01 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Increment SHLVL in environment.
*/
static char	increment_shlvl(t_list *env_var, t_list **env, t_list **gc)
{
	char	*shlvl_value;
	char	*shlvl;
	t_var	*var;

	if (!env_var)
	{
		var = var_init("SHLVL=1", gc);
		if (!var)
			return (FAILURE);
		gc_list_push_back(env, var, gc);
		return (SUCCESS);
	}
	shlvl_value = ft_itoa(ft_atoi(((t_var *)env_var->data)->value) + 1);
	if (!shlvl_value)
		return (FAILURE);
	gc_register(gc, shlvl_value);
	shlvl = gc_strjoin("SHLVL=", shlvl_value, gc);
	gc_free(gc, (void **)&shlvl_value);
	var = var_init(shlvl, gc);
	if (!shlvl || !var)
		return (FAILURE);
	env_update(env, var, gc);
	gc_free(gc, (void **)&shlvl);
	return (SUCCESS);
}

/*
**	Create a list env from main envp tab.
*/
t_list	*env_init(char **envp, t_list **gc)
{
	unsigned int	i;
	t_list			*env;
	t_var			*var;
	t_list			*env_var;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = var_init(envp[i], gc);
		if (!var || !var->value)
			return (NULL);
		gc_list_push_back(&env, var, gc);
		i++;
	}
	env_var = ft_list_find(env, "SHLVL", &is_var);
	if (!increment_shlvl(env_var, &env, gc))
		return (NULL);
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
		tmp = gc_strjoin(((t_var *)env->data)->name,
				((t_var *)env->data)->equal, gc);
		if (!tmp)
			return (NULL);
		envp[i] = gc_strjoin(tmp, ((t_var *)env->data)->value, gc);
		gc_free(gc, (void **)&tmp);
		if (!envp[i])
			return (NULL);
		env = env->next;
		i++;
	}
	return (envp);
}

/*
**	Update a variable in environment.
*/
void	env_update(t_list **env, t_var *var, t_list **gc)
{
	t_list	*env_var;

	env_var = ft_list_find(*env, var->name, &is_var);
	if (!env_var)
		gc_list_push_back(env, var, gc);
	else if (*(var->equal))
	{
		gc_free(gc, (void **)&((t_var *)env_var->data)->equal);
		((t_var *)env_var->data)->equal = var->equal;
		gc_free(gc, (void **)&((t_var *)env_var->data)->value);
		((t_var *)env_var->data)->value = var->value;
	}
}
