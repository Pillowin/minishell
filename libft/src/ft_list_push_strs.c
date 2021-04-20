/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_strs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:40:37 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 21:05:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Crée une nouvelle liste en y mettant les chaines de caracteres pointées
**	par les éléments tableau strs.
**	Edit : this is a modified func with ordered list
*/

t_list	*ft_list_push_strs(size_t size, char **strs)
{
	size_t	i;
	t_list	*list;
	t_list	*begin;

	if (!size)
		return (NULL);
	list = ft_create_elem(strs[0]);
	begin = list;
	i = 1;
	while (i < size)
	{
		list->next = ft_create_elem(strs[i]);
		list = list->next;
		i++;
	}
	return (begin);
}
