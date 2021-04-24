/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:16:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 00:51:42 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create a list from main envp
*/
t_list	*env_init(char **envp)
{
	unsigned int	i;
	t_list			*env;
	t_var			*var;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = var_init(get_var_name(envp[i]), get_var_equal(envp[i]), get_var_value(envp[i]));
		if (!var)
			return (NULL);
		ft_list_push_back(&env, var);
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
