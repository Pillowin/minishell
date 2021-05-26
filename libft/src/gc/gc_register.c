/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:58:59 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Register ptr to list gc.
*/
void	gc_register(t_list **gc, void *ptr)
{
	ft_list_push_back(gc, ptr);
}
