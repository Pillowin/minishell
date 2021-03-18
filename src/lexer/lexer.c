/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:07:26 by agautier          #+#    #+#             */
/*   Updated: 2021/03/14 19:2:06 by aagtetrer        ###   ########.fr       */
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
**	- Sauter les espaces
**	- Recuperer le token courrant
**	- Sauter les espaces
**	- Recuperer le token suivant
**
**	- Compter le nombre de token
**	- Creer une liste avec tous les tokens
**
**	- Verifier les erreurs ? // TODO:
**
**	- Creer un arbre a partir des priorites et en regroupant les tokens (ranger en préfix ?)
**
**	echo antoine > toto gautier | wc -w
**
**	t_command[0] = "echo"
**	t_command[1] = "antoine"
**	t_command[2] = "gautier"
**
**	t_redir[0] = "> toto"
**
**	PIPE
**
**	t_command[0] = "wc"
**	t_command[1] = "-w"
**
**	- On le trie par priorite pour obtenir
**	
**	PIPE
**
**	t_redir[0] = "> toto"
**
**	t_command[0] = "echo"
**	t_command[1] = "antoine"
**	t_command[2] = "gautier"
**
**	t_command[0] = "wc"
**	t_command[1] = "-w"
**
*/

void	lexer(char *av)
{
	t_lexer			*lexer;
	t_list			*tokens;

	lexer = lexer_init(av);
	tokens = NULL;
	while (lexer->i < lexer->str_len)
	{
		lexer_skip_spaces(lexer);
		ft_list_push_back(&tokens, lexer_get_token(lexer));
	}
	ft_list_foreach(tokens, &token_print); // TODO: remove
	printf("\n");
	// TODO: parcourir la liste a la recherche de token dans l'ordre des priorites
	parse_tokens(tokens);
}
