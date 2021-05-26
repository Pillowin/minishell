/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 21:54:12 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 18:50:45 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
