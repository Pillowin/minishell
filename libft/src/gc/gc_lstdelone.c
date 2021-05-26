/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:39:42 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:42 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
