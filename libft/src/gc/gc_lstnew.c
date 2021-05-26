/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 20:08:51 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:46 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Alloue (avec malloc(3)) et renvoie un nouvel élément.
**	la variable data est initialisée à l’aide de la valeur du paramètre
**	data.
**	La variable ’next’ est initialisée à NULL.
*/
t_list	*gc_lstnew(void *data, t_list **gc)
{
	t_list	*list;

	list = (t_list *)gc_calloc(gc, 1, (sizeof(*list)));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = 0;
	return (list);
}
