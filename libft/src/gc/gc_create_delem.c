/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:50:54 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:09 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Crée un nouvel élement dans la liste doublement chaînée.
*/
t_dlist	*gc_create_delem(t_list **gc, void *data)
{
	t_dlist	*list;

	list = (t_dlist *)gc_calloc(gc, 1, sizeof(*list));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
