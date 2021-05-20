/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_end_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:45:26 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:19 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoi 1 si le caractère C est un espace ou un retour à la ligne,
**	sinon elle renvoi 0.
*/
int	ft_is_end_word(char c)
{
	if (!c || c == ' ' || c == '\n')
		return (1);
	return (0);
}
