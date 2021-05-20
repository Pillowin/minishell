/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:03:44 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 19:04:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
