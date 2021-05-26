/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:55:45 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:45:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_word_len(const char *s, int index, char c)
{
	int	i;
	int	word_count;
	int	char_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			word_count++;
		char_count = 0;
		if (word_count == index + 1)
		{
			while (s[i] && s[i++] != c)
				char_count++;
			return (char_count);
		}
		else
			while (s[i] && s[i] != c)
				i++;
	}
	return (0);
}

static char	*ft_parse_word(const char *s, char *res, int index, char c)
{
	int		i;
	int		j;
	int		word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			word_count++;
		if (word_count == index + 1)
		{
			j = 0;
			while (s[i] && s[i] != c)
				res[j++] = s[i++];
			res[j] = '\0';
			return (res);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return ((char *) NULL);
}

static char	**ft_free_tabs(char **t, int i)
{
	while (i >= 0)
	{
		free(t[i]);
		i--;
	}
	free(t);
	return (NULL);
}

/*
**	Alloue (avec malloc(3)) et retourne un tableau de chaines de caracteres
**	obtenu en séparant ’s’ à l’aide du caractère ’c’, utilisé comme délimiteur.
**	Le tableau est terminé par NULL.
*/
char	**ft_split(char const *s, char c)
{
	char	**t;
	int		nb_word;
	int		word_len;
	int		i;

	if (!s)
		return (NULL);
	nb_word = ft_count_words(s, c);
	t = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!t)
		return ((char **) NULL);
	i = 0;
	while (i < nb_word)
	{
		word_len = ft_word_len(s, i, c);
		t[i] = (char *)malloc(sizeof(char *) * (word_len + 1));
		if (!t[i])
			return (ft_free_tabs(t, i - 1));
		t[i] = ft_parse_word(s, t[i], i, c);
		i++;
	}
	t[i] = (char *) NULL;
	return (t);
}
