/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaqutig <mamaqutig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:56:01 by agautier          #+#    #+#             */
/*   Updated: 2021/03/29 19:33:2 by mamaqutig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Alloue (avec malloc(3)) et retourne une nouvelle chaine, résultat de la
**	concaténation de s1 et s2.
*/

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (dst);
}
