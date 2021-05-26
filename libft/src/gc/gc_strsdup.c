/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:40:17 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:38 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Alloue un tableau de chaîne de caractères, puis alloue une chaîne de
**	caractère dans ce dernier.
*/
int	gc_strsdup(char ***strs, size_t size, char *str, t_list **gc)
{
	*strs = (char **)gc_calloc(gc, size + 1, sizeof(**strs));
	if (!(*strs))
		return (FAILURE);
	*strs[0] = ft_strdup(str);
	if (!(*strs[0]))
		return (FAILURE);
	gc_register(gc, **strs);
	return (SUCCESS);
}
