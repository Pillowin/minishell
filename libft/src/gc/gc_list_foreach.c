/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:37:12 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:05 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Applique la fonction passé en paramètre à chaque élement de la liste.
*/
void	gc_list_foreach(t_list *begin_list, void (*f)(void *, t_list **),
						t_list **gc)
{
	while (begin_list)
	{
		(*f)(begin_list->data, gc);
		begin_list = begin_list->next;
	}
}
