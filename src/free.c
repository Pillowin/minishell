/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:45:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 21:41:552 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: remove both ?

void	gc_free_tab(void **data, t_list **gc)
{
	unsigned int	i;

	i = 0;
	while ((char **)(data)[i])
	{
		gc_free(gc, (void **)&(data[i]));
		i++;
	}
	gc_free(gc, (void **)&data);
}

void	gc_lstdel(void **list, t_list **gc)
{
	gc_list_foreach(*(t_list **)list, &token_destroy, gc);
	gc_list_clear(*(t_list **)list, gc);
}
