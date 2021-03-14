/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:07:26 by agautier          #+#    #+#             */
/*   Updated: 2021/03/14 19:2:06 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->str[lexer->i] == ' ')
		lexer->i += 1;
	lexer->c = lexer->str[lexer->i];
}

t_token	*lexer_get_token(t_lexer *lexer)
{
	if (lexer->str_len > lexer->i + 1 && lexer->c == '>'
		&& lexer->str[lexer->i + 1] == '>')
		return (lexer_advance_current(lexer, TOKEN_DGREAT));
	if (lexer->c == '|')
		return (lexer_advance_current(lexer, TOKEN_PIPE));
	if (lexer->c == '<')
		return (lexer_advance_current(lexer, TOKEN_LESS));
	if (lexer->c == '>')
		return (lexer_advance_current(lexer, TOKEN_GREAT));
	if (lexer->c == ';')
		return (lexer_advance_current(lexer, TOKEN_SEMI));
	if (lexer->c == '\n')
		return (lexer_advance_current(lexer, TOKEN_NEWLINE));
	return (lexer_advance_word(lexer));
}

/*
**	command = bonjour ||; >> < toto bonjour
**	- Sauter les espaces
**	- Recuperer le token courrant
**	- Sauter les espaces
**	- Recuperer le token suivant
*/

void	lexer(char *av)
{
	t_lexer	*lexer;

	lexer = lexer_init(av);
	while (lexer->i < lexer->str_len)
	{
		lexer_skip_spaces(lexer);
		token_print(lexer_get_token(lexer));
	}
}
