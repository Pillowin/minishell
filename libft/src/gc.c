/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:31:04 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 14:444:76 byagattierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Assign a new ptr with ft_calloc and register it to list gc.
*/

void	*gc_calloc(t_list **gc, size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char*)malloc(size * count);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		ptr[i] = '\0';
		i++;
	}
	ft_list_push_back(gc, ptr);
	return (ptr);
}

/*
**	Register ptr to list gc.
*/

void	gc_set(t_list **gc, void *ptr)
{
	ft_list_push_back(gc, ptr);
}

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
**	Free a ptr assign it to NULL and remove it from list gc.
*/

void	gc_free(t_list **gc, void **ptr)
{
	ft_list_remove_if(gc, *ptr, &cmp, &free);
	*ptr = NULL;
}

/*
**	Free all ptr in list gc, destroy list gc.
*/

void	gc_clean(t_list **gc)
{
	ft_list_foreach(*gc, &free);
	ft_list_clear(*gc, &ft_free);
	*gc = NULL;
}
