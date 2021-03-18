/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:18:11 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/04 19:07:54 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
**	Crée un nouvel élément de type t_list.
*/

t_list	*ft_create_elem(void *data)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	return (list);
}
