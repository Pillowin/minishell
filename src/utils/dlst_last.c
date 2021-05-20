/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:52:44 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:18 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoi le dernier élement de la liste doublement chaînée.
*/
t_dlist	*dlst_last(t_dlist *dlist)
{
	while (dlist && dlist->next)
		dlist = dlist->next;
	return (dlist);
}
