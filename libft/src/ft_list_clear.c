/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:55:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/09 21:27:05 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Retire et libère l’ensemble des éléments de la liste.
*/

void	ft_list_clear(t_list *begin_list, void (*free_fct)(void **))
{
	t_list	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		free_fct((void **)&begin_list);
		begin_list = tmp;
	}
}
