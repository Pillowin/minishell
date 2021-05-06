/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 01:18:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 22:110:00 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create t to create a new var.
*/

static char	tab_init(char **s1, char **s2, char **s3)
{
	*s1 = ft_strdup(*s1);
	if (!*s1)
		return (FAILURE);
	*s2 = ft_strdup(*s2);
	if (!*s2)
	{
		ft_free((void **)s1);
		return (FAILURE);
	}
	*s3 = ft_strdup(*s3);
	if (!*s3)
	{
		ft_free((void **)s1);
		ft_free((void **)s2);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
**	Print pretty prompt and set PS1if needed.
*/

char	prompt(t_list **env)
{
	t_list	*prompt;
	t_var	*var;
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = "PS1";
	s2 = "=";
	s3 = DEFAULT_PROMPT;
	prompt = ft_list_find(*env, (void *)"PS1", &is_var);
	if (!prompt)
	{
		if (!tab_init(&s1, &s2, &s3))
			return (FAILURE);
		var = var_init(s1, s2, s3);
		if (!var)
			return (FAILURE);
		ft_list_push_back(env, var);
		prompt = ft_lstlast(*env);
	}
	// else if (!((((t_var *)prompt->data)->value))) //TODO: vérif si ok
	// {
	// 	if (!tab_init(&s1, &s2, &s3))
	// 		return (FAILURE);
	// 	((t_var *)prompt->data)->equal = s2;
	// 	((t_var *)prompt->data)->value = s3;
	// }
	ft_putstr_fd(((t_var *)prompt->data)->value, STDOUT_FILENO);
	return (SUCCESS);
}
