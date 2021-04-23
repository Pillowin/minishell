/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:55:19 by agautier          #+#    #+#             */
/*   Updated: 2021/04/22 13:39:38 by agautier         ###   ########.fr       */
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
	return ((char *)NULL);
}

static void	ft_free_tabs(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

/*
**	Alloue (avec malloc(3)) et retourne un tableau de chaines de caracteres
**	obtenu en séparant ’s’ à l’aide du caractère ’c’, utilisé comme délimiteur.
**	Le tableau est terminé par NULL.
*/

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_word;
	int		word_len;
	int		i;

	if (!s)
		return (0);
	nb_word = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_word + 1))))
		return ((char **)NULL);
	i = 0;
	while (i < nb_word)
	{
		word_len = ft_word_len(s, i, c);
		if (!(tab[i] = (char *)malloc(sizeof(char *) * (word_len + 1))))
		{
			ft_free_tabs(tab, i - 1);
			return ((char **)NULL);
		}
		tab[i] = ft_parse_word(s, tab[i], i, c);
		i++;
	}
	tab[i] = (char *)NULL;
	return (tab);
}
