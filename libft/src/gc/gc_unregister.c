/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_unregister.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:59:36 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:38 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**
*/
static int	cmp(void *data, void *ref)
{
	if (data == ref)
		return (0);
	return (1);
}

/*
**
*/
void	gc_unregister(t_list **gc, void *ptr)
{
	if (!ptr)
		return ;
	ft_list_remove_if(gc, ptr, &cmp, NULL);
}
