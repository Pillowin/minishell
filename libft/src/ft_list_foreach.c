/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:07 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/04 18:46:26 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
**	Applique une fonction donnée en paramètre à la valeur contenue dans
**	chaque élément de la liste.
*/

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}
