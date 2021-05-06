/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggieteer <ggieteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:38:52 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/13 1700:316by aggerteer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_lexer.
*/

int	lexer_init(char *str, t_lexer **lexer)
{
	if (!my_calloc(1, sizeof(**lexer), (void **)lexer))
		return (FAILURE);
	(*lexer)->str = str;
	(*lexer)->str_len = ft_strlen(str);
	(*lexer)->i = 0;
	(*lexer)->c = str[(*lexer)->i];
	return (SUCCESS);
}

/*
**	Create and return t_token from next token found after cursor.
*/

t_token	*lexer_get_token(t_lexer *lexer, t_err *err)
{
	unsigned int		i;
	const char			tab_data[10] = {
		' ', '|', '<', '>', ';', '"', '\'', '\\', '$', '\n'};
	const t_tok_type	tab_type[10] = {
		TOK_SPACE, TOK_PIPE, TOK_LESS, TOK_GREAT, TOK_SEMI,
		TOK_DQUOTE, TOK_QUOTE, TOK_BSLASH, TOK_DOLLAR, TOK_NEWLINE};

	i = 0;
	while (i < 10)
	{
		if (lexer->c == tab_data[i])
			return (lexer_advance_current(lexer, tab_type[i], err));
		i++;
	}
	return (lexer_advance_word(lexer, err));
}

/*
**	Entry point for parsing.
*/

int	lexer(char *input, t_err *err, t_list *env)
{
	t_lexer	*lexer;
	t_list	*tokens;
	t_token	*token;

	if (!lexer_init(input, &lexer))
		return ((long)error(err, MALLOC, NULL, NULL));
	tokens = NULL;
	while (lexer->i < lexer->str_len)
	{
		token = lexer_get_token(lexer, err);
		if (!token)
		{
			ft_lstdel((void **)&tokens);
			ft_free((void **)&(lexer));
			return (FAILURE);
		}
		ft_list_push_back(&tokens, token);
	}
	ft_free((void **)&(lexer));
	if (!parser(&tokens, err, env))
		return (FAILURE);
	return (SUCCESS);
}
