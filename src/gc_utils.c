/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:45:29 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 20:11:566 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	gc_list_push_back(t_list **begin_list, void *data, t_list **gc)
{
	t_list	*current;

	if (*begin_list == NULL)
	{
		*begin_list = ft_create_elem(data);
		gc_register(gc, *begin_list);
		return ;
	}
	current = *begin_list;
	while (current->next)
		current = current->next;
	current->next = ft_create_elem(data);
	gc_register(gc, current->next);
}

void	gc_list_clean(t_list *begin_list, t_list **gc)
{
	t_list	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		gc_free(gc, (void **)&begin_list);
		begin_list = tmp;
	}
}

void	gc_list_foreach(t_list *begin_list, void (*f)(void *, t_list **), t_list **gc)
{
	while (begin_list)
	{
		(*f)(begin_list->data, gc);
		begin_list = begin_list->next;
	}
}

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
