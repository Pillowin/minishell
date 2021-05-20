/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:39:42 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:06 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Supprime un élement de la liste.
*/
void	gc_lstdelone(t_list *lst, void (*del)(void *, t_list **), t_list **gc)
{
	if (!lst)
		return ;
	if (del)
		del(lst->data, gc);
	gc_free(gc, (void **)&lst);
}
