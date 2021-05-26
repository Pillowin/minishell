/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list_remove_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:38:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Supprime de la liste la variable passé en paramètre.
*/
void	gc_list_remove_var(t_list **begin_list, void *data_ref, t_list **gc)
{
	t_list	*list_ptr;
	t_list	*prev;

	list_ptr = *begin_list;
	prev = NULL;
	while (list_ptr)
	{
		if (!ft_strcmp(((t_var *)list_ptr->data)->name, data_ref))
		{
			if (prev)
				prev->next = list_ptr->next;
			else
				*begin_list = (*begin_list)->next;
			var_destroy(list_ptr->data, gc);
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
