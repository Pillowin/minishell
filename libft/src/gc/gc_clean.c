/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:00:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:00:32 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free all ptr in list gc, destroy list gc.
*/
void	gc_clean(t_list **gc)
{
	t_list	*curr;
	t_list	*next;

	curr = *gc;
	while (curr)
	{
		next = NULL;
		if (curr->next)
			next = curr->next;
		ft_free((void **)&(curr->data));
		ft_free((void **)&curr);
		curr = next;
	}
	*gc = NULL;
}
