/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:59:57 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:00:05 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free a ptr assign it to NULL and remove it from list gc.
*/
void	gc_free(t_list **gc, void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	gc_unregister(gc, *ptr);
	ft_free(ptr);
}
