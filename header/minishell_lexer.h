/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:12:17 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/12 18:32:116 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXER_H
# define MINISHELL_LEXER_H

typedef struct	s_lexer
{
	char			*str;
	unsigned int	str_len;
	char			c;
	unsigned int	i;
}				t_lexer;

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

typedef struct	s_token
{
	t_tok_type	type;
	char		**data;
}				t_token;

/*
**	lexer.c
*/

int				lexer(char *input, t_err *err);
int				lexer_init(char *str, t_lexer **lexer);
t_token			*lexer_get_token(t_lexer *lexer, t_err *err);

/*
**	lexer_advance.c
*/

void			lexer_advance(t_lexer *lexer, unsigned int len);
t_token			*lexer_advance_word(t_lexer *lexer, t_err *err);
t_token			*lexer_advance_current(t_lexer *lexer, t_tok_type type, t_err *err);

/*
**	token.c
*/

int				token_init(t_tok_type type, char **data, t_token **token);
void			token_destroy(void *ptr);

/*
**	debug.c
*/

char			*token_type_to_str(int type);
void			token_print(void *token);

#endif
