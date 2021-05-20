/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:52:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:24 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoi le nombre de caractère écrit.
*/
int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
