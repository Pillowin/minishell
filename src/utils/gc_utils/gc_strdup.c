/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:43:34 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:09 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloue une chaîne de caractère.
*/
char	*gc_strdup(char *str, t_list **gc)
{
	str = ft_strdup(str);
	if (!str)
		return (NULL);
	gc_register(gc, str);
	return (str);
}
