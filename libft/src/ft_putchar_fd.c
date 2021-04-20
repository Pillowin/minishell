/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:46:43 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 18:40:28 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Écrit le caractère ’c’ sur le file descriptor donné.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
