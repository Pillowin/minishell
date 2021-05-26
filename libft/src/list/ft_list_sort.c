/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:46:42 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:10:30 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_list_swap(t_list *list)
{
	void	*data;

	data = list->data;
	list->data = list->next->data;
	list->next->data = data;
}

/*
**	Trie par ordre croissant le contenu de la liste, en comparant deux
**	éléments grâce à une fonction de comparaison de données des deux éléments.
*/
void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*curr;
	t_list	*tmp;

	curr = *begin_list;
	while (curr != NULL)
	{
		tmp = *begin_list;
		while (tmp->next != NULL)
		{
			if ((*cmp)(tmp->data, tmp->next->data) > 0)
				ft_list_swap(tmp);
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}
