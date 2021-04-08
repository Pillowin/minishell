/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggieteer <ggieteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:07:26 by agautier          #+#    #+#             */
/*   Updated: 2021/03/14 19:2:063by aggerteer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_lexer.
*/

t_lexer	*lexer_init(char *str)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)ft_calloc(1, sizeof(*lexer));
	if (!lexer)
		return (NULL);
	lexer->str = str;
	lexer->str_len = ft_strlen(str);
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return (lexer);
}

/*
**	Create and return t_token from next token found after cursor.
**
**	TODO: make prettier
*/

t_token	*lexer_get_token(t_lexer *lexer)
{
	if (lexer->str_len > lexer->i + 1 && lexer->c == '>'
		&& lexer->str[lexer->i + 1] == '>')
		return (lexer_advance_current(lexer, TOK_DGREAT));
	if (lexer->c == ' ')
		return (lexer_advance_current(lexer, TOK_SPACE));
	if (lexer->c == '|')
		return (lexer_advance_current(lexer, TOK_PIPE));
	if (lexer->c == '<')
		return (lexer_advance_current(lexer, TOK_LESS));
	if (lexer->c == '>')
		return (lexer_advance_current(lexer, TOK_GREAT));
	if (lexer->c == ';')
		return (lexer_advance_current(lexer, TOK_SEMI));
	if (lexer->c == '"')
		return (lexer_advance_current(lexer, TOK_DQUOTE));
	if (lexer->c == '\'')
		return (lexer_advance_current(lexer, TOK_QUOTE));
	if (lexer->c == '\\')
		return (lexer_advance_current(lexer, TOK_BSLASH));
	if (lexer->c == '$')
		return (lexer_advance_current(lexer, TOK_DOLLAR));
	if (lexer->c == '\n')
		return (lexer_advance_current(lexer, TOK_NEWLINE));
	return (lexer_advance_word(lexer));
}
/*
**	Entry point for parsing.
**
**	TODO: remove debug print
**	TODO: parcourir la liste a la recherche de token dans l'ordre des priorites
*/

void	lexer(char *av)
{
	t_lexer			*lexer;
	t_list			*tokens;

	lexer = lexer_init(av);
	tokens = NULL;
	while (lexer->i < lexer->str_len)
		ft_list_push_back(&tokens, lexer_get_token(lexer));
	// ft_list_foreach(tokens, &token_print);
	// printf("----------------------------------------------------------------\n");
	parse_tokens(&tokens);
	printf("\n");
}
