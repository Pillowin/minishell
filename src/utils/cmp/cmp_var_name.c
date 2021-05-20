/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:36:21 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 18:36:58 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Compare name of a t_var.
*/
int	cmp_var_name(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}
