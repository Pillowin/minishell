/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 01:18:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/04 22:34:32 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create t to create a new var.
*/

static char	**tab_init(char *s1, char *s2, char *s3)
{
	char	**t;

	t = (char **)ft_calloc(3, sizeof(*t));
	if (!t)
		return (NULL);
	t[0] = ft_strdup(s1);
	if (!t[0])
	{
		ft_free_tab((void **)t);
		return (NULL);
	}
	t[1] = ft_strdup(s2);
	if (!t[1])
	{
		ft_free_tab((void **)t);
		return (NULL);
	}
	t[2] = ft_strdup(s3);
	if (!t[2])
	{
		ft_free_tab((void **)t);
		return (NULL);
	}
	return (t);
}

/*
**	Print pretty prompt and set PS1if needed.
*/

char	prompt(t_list **env)
{
	t_list	*prompt;
	char	**t;
	t_var	*var;

	prompt = ft_list_find(*env, (void *)"PS1", &is_var);
	if (!prompt)
	{
		t = tab_init("PS1", "=", DEFAULT_PROMPT);
		var = var_init(t[0], t[1], t[2]);
		if (!var)
			return (FAILURE);
		ft_list_push_back(env, var);
		prompt = ft_lstlast(*env);
	}
	else if (!((((t_var *)prompt->data)->value)))
	{
		t = tab_init("PS1", "=", DEFAULT_PROMPT);
		((t_var *)prompt->data)->equal = t[1];
		((t_var *)prompt->data)->equal = t[2];
	}
	ft_putstr_fd(((t_var *)prompt->data)->value, STDOUT_FILENO);
	return (SUCCESS);
}
