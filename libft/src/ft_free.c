/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:27:51 by agautier          #+#    #+#             */
/*   Updated: 2020/11/11 14:22:23 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free un pointeur et le met a NULL.
*/

int	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (0);
}
