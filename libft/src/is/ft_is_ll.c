/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:52:57 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/29 13:53:01 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
**	Return 1 is number in str can be stored in long long, else return 0.
*/
int	ft_is_ll(const char *str)
{
	unsigned long long	res;
	unsigned char		i;
	unsigned char		neg;

	neg = 0;
	i = 0;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	res = 0;
	while (str[i] && is_digit(str[i]))
	{
		if (i > 20)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > (unsigned long long)__LONG_LONG_MAX__ + neg)
		return (0);
	return (1);
}
