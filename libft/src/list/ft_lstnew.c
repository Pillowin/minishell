/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:02:47 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 18:51:30 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Alloue (avec malloc(3)) et renvoie un nouvel élément.
**	la variable data est initialisée à l’aide de la valeur du paramètre
**	data.
**	La variable ’next’ est initialisée à NULL.
*/
t_list	*ft_lstnew(void *data)
{
	t_list	*list;

	list = (t_list *)malloc((sizeof(*list)));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = 0;
	return (list);
}
