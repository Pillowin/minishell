/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:03:44 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:08 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free each case of an array.
*/
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
