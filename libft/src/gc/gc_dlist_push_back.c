/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_dlist_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:51:31 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:08 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Ajoute un élement à la fin de la liste doublement chaînée.
*/
void	gc_dlist_push_back(t_list **gc, t_dlist **begin_list, void *data)
{
	t_dlist	*curr;

	if (*begin_list == NULL)
	{
		*begin_list = gc_create_delem(gc, data);
		return ;
	}
	curr = *begin_list;
	while (curr->next)
		curr = curr->next;
	curr->next = gc_create_delem(gc, data);
	curr->next->prev = curr;
}
