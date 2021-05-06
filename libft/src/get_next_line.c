/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:55:35 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/05 00:01:27 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*str;

// 	if (!len || !s || start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (!(str = malloc(sizeof(char) * (len + 1))))
// 		return (NULL);
// 	ft_memcpy(str, s + start, len);
// 	str[len] = '\0';
// 	return (str);
// }

void	tofree(char ***str)
{
	free(**str);
	**str = NULL;
}

int		get_next_part(char ***line, char **str, char **tmp, int nb)
{
	char *test;

	if (!(test = ft_strchr(*str, '\n')))
	{
		test = ft_strchr(*str, '\0');
		nb = 0;
	}
	else
		nb = 1;
	if (!(**line = ft_substr(*str, 0, ft_strlen(*str) - ft_strlen(test))))
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	if (nb == 1)
	{
		*tmp = *str;
		*str = ft_substr(test + 1, 0, ft_strlen(test + 1));
		free(*tmp);
	}
	else
		tofree(&str);
	return (nb);
}

int		get_next_line(int fd, char **line)
{
	char		*test;
	char		*tmp;
	static char *str = NULL;
	int			nb;

	tmp = NULL;
	if (!str)
		str = ft_strdup("");
	if (!tmp)
		tmp = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (fd < 0 || !line || read(fd, tmp, 0) == -1)
		return (-1);
	while (!(ft_strchr(str, '\n')) && (nb = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[nb] = '\0';
		test = str;
		str = ft_strjoin(str, tmp);
		free(test);
	}
	free(tmp);
	tmp = NULL;
	nb = get_next_part(&line, &str, &tmp, nb);
	return (nb);
}
