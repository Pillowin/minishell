/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list_rm_tok_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:39:07 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:48 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Supprime de la liste l'élement passé en paramètre si ce dernier est
**	égal à la data comparé.
*/
void	gc_list_rm_tok_if(t_list **begin_list, void *data_ref,
							int (*cmp)(), t_list **gc)
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
			token_destroy(list_ptr->data, gc);
			gc_free(gc, (void **)&list_ptr);
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
