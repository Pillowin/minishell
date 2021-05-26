/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:48:06 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:18:25 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_in_ptr(int n, char *ptr, int *index)
{
	if (n == -2147483648)
	{
		ptr[0] = '-';
		ptr[1] = '2';
		*index = *index + 2;
		n = 147483648;
	}
	else if (n < 0)
	{
		ptr[0] = '-';
		*index = *index + 1;
		n = -n;
	}
	if (n >= 0 && n <= 9)
		ptr[(*index)++] = (n + 48);
	else
	{
		ft_putnbr_in_ptr(n / 10, ptr, index);
		ft_putnbr_in_ptr(n % 10, ptr, index);
	}
}

static int	ft_nb_digit(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

/*
**	Alloue (avec malloc(3)) et retourne une chaine de caractères représentant
**	l’integer reçu en argument.
*/
char	*ft_itoa(int n)
{
	char	*ptr;
	int		nb_digit;
	int		index;

	index = 0;
	nb_digit = ft_nb_digit(n);
	ptr = malloc(sizeof(char) * (nb_digit + 1));
	if (!ptr)
		return (NULL);
	ft_putnbr_in_ptr(n, ptr, &index);
	ptr[nb_digit] = '\0';
	return (ptr);
}
