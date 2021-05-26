/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:06:18 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:44 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free an entire list and his content.
*/
void	gc_lstdel(void **list, t_list **gc)
{
	gc_list_foreach(*(t_list **)list, &token_destroy, gc);
	gc_list_clear(*(t_list **)list, gc);
}
