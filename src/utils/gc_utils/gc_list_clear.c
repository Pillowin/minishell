/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:36:22 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:51:45 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Free la liste passé en paramètre.
*/
void	gc_list_clear(t_list *begin_list, t_list **gc)
{
	t_list	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		gc_free(gc, (void **)&begin_list);
		begin_list = tmp;
	}
}
