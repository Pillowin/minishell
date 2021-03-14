/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:56:37 by agautier          #+#    #+#             */
/*   Updated: 2021/03/14 20:00:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_advance(t_lexer *lexer, unsigned int len)
{
	while (len)
	{
		if (lexer->i < lexer->str_len && lexer-> c != '\0')
		{
			lexer->i += 1;
			lexer->c = lexer->str[lexer->i];
		}
		len--;
	}
}

t_token	*lexer_advance_word(t_lexer *lexer)
{
	char	*str;
	int		str_len;
	int		i;

	str_len = 0;
	while (lexer->str[lexer->i + str_len] != ' '
		&& lexer->str[lexer->i + str_len] != '\n')
		str_len++;
	str = (char *)ft_calloc(str_len + 1, sizeof(*str));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = lexer->str[lexer->i + i];
		i++;
	}
	lexer_advance(lexer, str_len);
	return (token_init(TOKEN_WORD, str));
}

t_token	*lexer_advance_current(t_lexer *lexer, int type)
{
	char	*data;
	t_token	*token;

	if (type == TOKEN_DGREAT)
	{
		data = (char *)ft_calloc(3, sizeof(char));
		data[0] = '>';
		data[1] = '>';
		data[2] = '\0';
		lexer_advance(lexer, 2);
	}
	else
	{
		data = (char *)ft_calloc(2, sizeof(char));
		data[0] = lexer->c;
		data[1] = '\0';
		lexer_advance(lexer, 1);
	}
	token = token_init(type, data);
	return (token);
}
