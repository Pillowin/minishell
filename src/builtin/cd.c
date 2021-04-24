/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:13:43 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 22:39:335 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}

/*
**	Attribute current path to name 
*/
static char	update_var(t_list **env, char *name)
{
	t_list	*lst;
	char	*path;
	// t_var	*var;

	path = getcwd(NULL, 0);
	if (!path)
		return (FAILURE);
	lst = ft_list_find(*env, (void *)name, &cmp);
	if (lst)
	{
		ft_free((void **)&(((t_var *)lst->data)->value));
		((t_var *)lst->data)->value = ft_strdup(path);
		if (!(((t_var *)lst->data)->value))
			return (FAILURE);
	}
	ft_free((void **)&path);
	return (SUCCESS);
}

/*
**	TODO: update PWD and OLD_PWD
*/
unsigned char	builtin_cd(t_token *cmd, t_list **env)
{
	t_list	*lst;

	if (!(cmd->data[1]))
	{
		if (!update_var(env, "OLDPWD"))
			return (FAILURE);

		// je vais dans HOME
		lst = ft_list_find(*env, "HOME", &cmp);
		if (lst)
		{
			if (!(((t_var *)lst->data)->value))
				return (FAILURE);
			if (chdir((((t_var *)lst->data)->value)) == -1)
			{
				printf("erreur de cd : %s\n", strerror(errno));
				return (FAILURE);	// TODO: use errno
			}
		}
		else
		{
			// HOME not set
		}

		if (!update_var(env, "PWD"))
			return (FAILURE);
	}
	else if (cmd->data[2])
		return (FAILURE);	//trop d'arguments
	else
	{
		if (!update_var(env, "OLDPWD"))
			return (FAILURE);

		// je change de dossier
		if (chdir(cmd->data[1]) == -1)
		{
			printf("erreur de cd : %s\n", strerror(errno));
			return (FAILURE);	// TODO: use errno
		}

		if (!update_var(env, "PWD"))
			return (FAILURE);
	}
	return (SUCCESS);
}
