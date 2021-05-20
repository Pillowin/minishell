/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:53:24 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:59:51 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ajoute une nouvelle variable dans la liste passé en paramètre.
*/
t_list	*lstdup(t_list *lst, t_list **gc)
{
	t_list	*begin;

	begin = NULL;
	while (lst)
	{
		gc_list_push_back(&begin, lst->data, gc);
		lst = lst->next;
	}
	return (begin);
}
