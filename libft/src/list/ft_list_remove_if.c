/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:55:08 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 18:51:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Efface de la liste tous les éléments dont la donnée comparée renvoie 0.
**
**	        0x00                   0x01                   0x02
**	┌-----------------┐    ┌-----------------┐    ┌-----------------┐
**	|                 |    |                 |    |                 |
**	|  - data = 42    |    |  - data = 21    |    |  - data = 42    |
**	|                 | -► |                 | -► |                 |
**	|  - next = 0x01  |    |  - next = 0x02  |    |  - next = NULL  |
**	|                 |    |                 |    |                 |
**	└-----------------┘    └-----------------┘    └-----------------┘
*/
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
							int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*list_ptr;
	t_list	*prev;

	list_ptr = *begin_list;
	prev = NULL;
	while (list_ptr)
	{
		if (!cmp(list_ptr->data, data_ref))
		{
			if (prev)
				prev->next = list_ptr->next;
			else
				*begin_list = (*begin_list)->next;
			if (free_fct && *free_fct)
				(*free_fct)(list_ptr->data);
			ft_free((void **)&list_ptr);
			if (!prev)
				list_ptr = (*begin_list);
			else
				list_ptr = prev->next;
			continue ;
		}
		prev = list_ptr;
		list_ptr = list_ptr->next;
	}
}
