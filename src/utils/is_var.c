/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:49:41 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:46 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoi 0 si l'élement correspond à la référence passé en paramètre.
*/
int	is_var(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}
