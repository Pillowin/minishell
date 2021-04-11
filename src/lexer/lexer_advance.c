/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:38:21 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 15:20:49 by agautier         ###   ########.fr       */
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
		if (lexer->i < lexer->str_len && lexer-> c != '\0')
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

t_token	*lexer_advance_word(t_lexer *lexer)
{
	char	**data;
	char	*str;
	int		str_len;
	int		i;

	data = (char **)ft_calloc(1 + 1, sizeof(*data));
	if (!data)
		return (NULL);
	str_len = 0;
	while (!ft_is_end_word(lexer->str[lexer->i + str_len])
		&& !ft_is_token(lexer->str[lexer->i + str_len]))
		str_len++;
	str = (char *)ft_calloc(str_len + 1, sizeof(*str));
	if (!str)
		return (NULL);
	*data = str;
	i = 0;
	while (i < str_len)
	{
		str[i] = lexer->str[lexer->i + i];
		i++;
	}
	lexer_advance(lexer, str_len);
	return (token_init(TOK_WORD, data));
}

/*
**	Create and return t_token from next token after cursor,
**	then position the cursor after the token.
**
**	TODO: Optimize ? Because specific case for >> is ugly
*/

t_token	*lexer_advance_current(t_lexer *lexer, int type)
{
	char	**data;
	t_token	*token;

	data = (char **)ft_calloc(1 + 1, sizeof(*data));
	if (!data)
		return (NULL);
	// if (type == TOK_DGREAT)
	// {
	// 	*data = (char *)ft_calloc(2 + 1, sizeof(**data));
	// 	if (!*data)
	// 		return (NULL);
	// 	(*data)[0] = '>';
	// 	(*data)[1] = '>';
	// 	lexer_advance(lexer, 2);
	// }
	// else
	// {
		*data = (char *)ft_calloc(1 + 1, sizeof(**data));
		if (!*data)
			return (NULL);
		(*data)[0] = lexer->c;
		lexer_advance(lexer, 1);
	// }
	token = token_init(type, data);
	return (token);
}














// /*
// **	Parse and return word
// */

// static char	*parse_tok_word(t_lexer *lexer)
// {
// 	char	*str;
// 	int		str_len;
// 	int		i;

// 	str_len = 0;
// 	while (!ft_is_end_word(lexer->str[lexer->i + str_len]))
// 		str_len++;
// 	str = (char *)ft_calloc(str_len + 1, sizeof(*str));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < str_len)
// 	{
// 		str[i] = lexer->str[lexer->i + i];
// 		i++;
// 	}
// 	return (str);
// }

// /*
// **	Create and return t_token from next TOK_WORD after cursor,
// **	then position the cursor after the word.
// **
// **	TODO: handle ' or " should
// **
// */

// t_token	*lexer_advance_word(t_lexer *lexer)
// {
// 	char			**data;
// 	unsigned int	i;

// 	data = (char **)ft_calloc(1 + 1, sizeof(*data));
// 	if (!data)
// 		return (NULL);
// 	i = 0;
// 	// echo toto'tata'titi'tu tu'ton ton
// 	while (!ft_is_end_word(lexer->str[lexer->i + i]))
// 	{
// 		if (lexer->str[lexer->i + i] == '\'')
// 		{
// 			*data = expand_quote(lexer);	// *data = tototatatiti
// 			// i = strlen(*data)
// 			// continue
// 		}
// 		i++;
// 	}
// 	// else
// 		*data = parse_tok_word(lexer);
// 	lexer_advance(lexer, ft_strlen(*data));
// 	return (token_init(TOK_WORD, data));
// }


/*
**	Increment cursor while current char is a space.
**	(to skip spaces between word)
*/

// void	lexer_skip_spaces(t_lexer *lexer)
// {
// 	while (lexer->str[lexer->i] == ' ')
// 		lexer->i += 1;
// 	lexer->c = lexer->str[lexer->i];
// }
