/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 01:18:19 by agautier          #+#    #+#             */
/*   Updated: 2021/04/25 01:28:51 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create tab to create a new var.
*/

static char	**tab_init(char *s1, char *s2, char *s3)
{
	char	**tab;

	tab = (char **)ft_calloc(3, sizeof(*tab));
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(s1);
	if (!tab[0])
	{
		ft_free_tab((void **)tab);
		return (NULL);
	}
	tab[1] = ft_strdup(s2);
	if (!tab[1])
	{
		ft_free_tab((void **)tab);
		return (NULL);
	}
	tab[2] = ft_strdup(s3);
	if (!tab[2])
	{
		ft_free_tab((void **)tab);
		return (NULL);
	}
	return (tab);
}

/*
**	Print pretty prompt and set PS1if needed.
*/

char	prompt(t_list **env)
{
	t_list	*prompt;
	char	**tab;
	t_var	*var;

	prompt = ft_list_find(*env, (void *)"PS1", &is_var);
	if (!prompt)
	{
		tab = tab_init("PS1", "=", DEFAULT_PROMPT);
		var = var_init(tab[0], tab[1], tab[2]);
		if (!var)
			return (FAILURE);
		ft_list_push_back(env, var);
		prompt = ft_lstlast(*env);
	}
	else if (!((((t_var *)prompt->data)->value)))
	{
		tab = tab_init("PS1", "=", DEFAULT_PROMPT);
		((t_var *)prompt->data)->equal = tab[1];
		((t_var *)prompt->data)->equal = tab[2];
	}
	ft_putstr_fd(((t_var *)prompt->data)->value, STDOUT_FILENO);
	return (SUCCESS);
}
