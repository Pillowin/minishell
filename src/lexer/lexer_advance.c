/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:06:55 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 21:22:24 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Advance cursor of len.
*/

void	lexer_advance(t_lexer *lexer, unsigned int len)
{
	while (len)
	{
		if (lexer->i < lexer->str_len && lexer->c != '\0')
		{
			lexer->i += 1;
			lexer->c = lexer->str[lexer->i];
		}
		len--;
	}
}

/*
**	Create and return t_token from next TOKEN_WORD after cursor,
**	then position the cursor after the word.
*/

t_token	*lexer_advance_word(t_lexer *lexer, t_err *err)
{
	char			**data;
	unsigned int	str_len;
	unsigned int	i;
	t_token			*token;

	if (!my_calloc(1, sizeof(*data), (void **)&data))
		return (error(err, MALLOC, NULL, NULL));
	str_len = 0;
	while (!ft_is_end_word(lexer->str[lexer->i + str_len])
		&& !ft_is_token(lexer->str[lexer->i + str_len]))
		str_len++;
	if (!my_calloc(str_len, sizeof(**data), (void **)data))
		return (error(err, MALLOC, (void **)&data, &ft_free));
	i = 0;
	while (i < str_len)
	{
		(*data)[i] = lexer->str[lexer->i + i];
		i++;
	}
	lexer_advance(lexer, str_len);
	if (!token_init(TOK_WORD, data, &token))
		return (error(err, MALLOC, (void **)data, &ft_free_tab));
	return (token);
}

/*
**	Create and return t_token from next TOKEN after cursor,
**	then position the cursor after the token.
*/

t_token	*lexer_advance_current(t_lexer *lexer, t_tok_type type, t_err *err)
{
	char	**data;
	t_token	*token;

	if (!my_strdup(&data, 1, &(lexer->c)))
		return (error(err, MALLOC, NULL, NULL));
	lexer_advance(lexer, 1);
	if (!token_init(type, data, &token))
		return (error(err, MALLOC, (void **)data, &ft_free_tab));
	return (token);
}
