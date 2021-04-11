/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:27:51 by agautier          #+#    #+#             */
/*   Updated: 2021/04/09 21:03:08 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free un pointeur et le met a NULL.
*/

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
