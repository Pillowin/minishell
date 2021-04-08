/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:51:10 by agautier          #+#    #+#             */
/*   Updated: 2021/04/08 19:05:05 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Applique une fonction donnée en paramètre à la valeur contenue dans
**	certains éléments de la liste.
*/

void	my_list_foreach_if(t_list *begin_list, void (*f)(t_list *,
		unsigned int), void *data_ref, int (*cmp)())
{
	t_list			*list;
	unsigned int	i;

	list = begin_list;
	i = 0;
	while (list)
	{
		if (!cmp(list->data, data_ref))
			(*f)(begin_list, i);
		list = list->next;
		i++;
	}
}
