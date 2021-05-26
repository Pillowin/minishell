/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:27:34 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:01:40 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Alloue (avec malloc(3)) et retourne une nouvelle chaine, résultat de la
**	concaténation de s1 et s2.
*/
char	*gc_strjoin(char const *s1, char const *s2, t_list **gc)
{
	char	*dst;
	size_t	len;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	s2_len = 0;
	if (s2)
		s2_len = ft_strlen(s2);
	len = s1_len + s2_len + 1;
	dst = ft_calloc(len, sizeof(*dst));
	if (!dst)
		return (NULL);
	if (s1)
		dst = ft_memcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, len);
	gc_register(gc, dst);
	return (dst);
}
