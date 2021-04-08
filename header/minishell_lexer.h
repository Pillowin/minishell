/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/08 19:10:36 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXER_H
# define MINISHELL_LEXER_H

typedef struct s_lexer
{
	char			*str;
	unsigned int	str_len;
	char			c;
	unsigned int	i;
}	t_lexer;

typedef enum
{
	TOK_UNKNOW = 0,
	TOK_SPACE,
	TOK_WORD,
	TOK_PIPE,
	TOK_LESS,
	TOK_GREAT,
	TOK_DGREAT,
	TOK_SEMI,
	TOK_DQUOTE,
	TOK_QUOTE,
	TOK_BSLASH,
	TOK_DOLLAR,
	TOK_NEWLINE,
	TOK_REDIR,
	TOK_COMMAND
}	t_tok_type;

typedef struct s_token
{
	t_tok_type	type;
	char		**data;
}	t_token;

/*
**	lexer.c
*/

void	lexer(char *av);

t_lexer	*lexer_init(char *str);
void	token_destroy(void *ptr);
void	lexer_advance(t_lexer *lexer, unsigned int len);
t_token	*lexer_advance_word(t_lexer *lexer);
t_token	*lexer_advance_current(t_lexer *lexer, int type);
void	lexer_skip_spaces(t_lexer *lexer);
t_token	*lexer_get_token(t_lexer *lexer);

/*
**	token.c
*/

t_token	*token_init(int type, char **data);
char	*token_type_to_str(int type);
void	token_print(void *token);

#endif
