/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 21:54:12 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/04 18:45:31 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
**	Renvoie le n-ième élément de la liste, sachant que le premier élément est
**	l’élément 0.
*/

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	if (!begin_list)
		return (NULL);
	while (begin_list->next && nbr)
	{
		begin_list = begin_list->next;
		nbr--;
	}
	if (nbr)
		return (NULL);
	return (begin_list);
}
