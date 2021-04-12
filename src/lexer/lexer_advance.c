/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:38:21 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 17:39:332 by agautier         ###   ########.fr       */
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

t_token	*lexer_advance_word(t_lexer *lexer, t_err *err)
{
	char	**data;
	// char			*str;
	unsigned int	str_len;
	unsigned int	i;
	t_token			*token;

	// data = (char **)ft_calloc(1 + 1, sizeof(*data));
	if (!my_calloc(1, sizeof(*data), (void **)&data))
	{
		// TODO: free
		return (error(err, MALLOC, NULL, NULL));
	}

	str_len = 0;
	while (!ft_is_end_word(lexer->str[lexer->i + str_len])
		&& !ft_is_token(lexer->str[lexer->i + str_len]))
		str_len++;

	*data = (char *)ft_calloc(str_len + 1, sizeof(**data));
	// printf("data = %s\n", *data);
	// if (!my_calloc(str_len, sizeof(**data), (void **)data))
	// {
	// 	// TODO: free
	// 	return (error(err, MALLOC, NULL, NULL));
	// }

	i = 0;
	while (i < str_len)
	{
		(*data)[i] = lexer->str[lexer->i + i];
		i++;
	}
	// printf("data = %s\n", *data);

	lexer_advance(lexer, str_len);
	// token = token_init(TOK_WORD, data);
	token = NULL;
	if (!token_init(TOK_WORD, data, &token))
	{
		// TODO: free lexer
		return (error(err, MALLOC, NULL, NULL));
	}
	// printf("token = %p\n", token);
	// printf("token type = %d\n", token->type);
	// printf("token data = %s\n", token->data[0]);
	// token_print(token);
	return (token);
}

/*
**	Create and return t_token from next token after cursor,
**	then position the cursor after the token.
*/

t_token	*lexer_advance_current(t_lexer *lexer, t_tok_type type, t_err *err)
{
	char	**data;
	t_token	*token;

	if (!ft_strsdup(&data, 1, &(lexer->c)))
		return (error(err, MALLOC, NULL, NULL));
	// data = (char **)ft_calloc(1 + 1, sizeof(*data));
	// if (!data)
	// {
	// 	// TODO: 
	// 	return (NULL);
	// }
	// *data = ft_strdup(&(lexer->c));
	// if ((!*data))
	// {
	// 	// TODO: 
	// 	return (NULL);
	// }
	lexer_advance(lexer, 1);
	// token = token_init(type, data);
	if (!token_init(type, data, &token))
	{
		// TODO: free lexer
		return (error(err, MALLOC, NULL, NULL));
	}
	return (token);
}


// - fonction principales (lexer, parser, expand)
// 	=> faire remonter l error au main
// 	- sous fonction = utilisation unique (expand_quote, expand_dquote)
// 		=> error()

// - fonction de "lib" = reutilisable (init, destroy, my_calloc)
// 	=> return null donc verifier son retour dans la fonction parente
