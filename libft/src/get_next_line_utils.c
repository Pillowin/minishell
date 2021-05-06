/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:55:58 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/05 00:01:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char		*ft_strchr(const char *s, int c)
// {
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (*s == '\0' && c == '\0')
// 		return ((char *)s);
// 	return (0);
// }

// void		*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t i;

// 	i = 0;
// 	if (dst == NULL && src == NULL)
// 		return (NULL);
// 	while (i < n && (dst || src))
// 	{
// 		((char *)dst)[i] = ((char *)src)[i];
// 		i++;
// 	}
// 	return ((char *)dst);
// }

// size_t		ft_strlen(const char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char		*ft_strdup(const char *s1)
// {
// 	int		s;
// 	char	*dest;

// 	s = ft_strlen(s1);
// 	if (!(dest = malloc(sizeof(char) * s + 1)))
// 		return (NULL);
// 	dest = ft_memcpy(dest, s1, s);
// 	dest[s] = '\0';
// 	return (dest);
// }

// char		*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*dst;
// 	size_t	tot;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	if (!(dst = malloc(sizeof(char) * tot)))
// 		return (NULL);
// 	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
// 	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2) + 1);
// 	return (dst);
// }
