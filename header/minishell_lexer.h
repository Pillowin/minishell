/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/03/21 19:09:32 by agautier         ###   ########.fr       */
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
	TOKEN_UNKNOW = 0,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_SEMI,
	TOKEN_NEWLINE,
	TOKEN_REDIR,
	TOKEN_COMMAND
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

/*
**	check_token.c
*/
void	check_semi(t_list *tokens, void *data, unsigned int i);
void	check_pipe(t_list *tokens, void *data, unsigned int i);
void	check_dgreat(t_list *tokens, void *data, unsigned int i);
void	check_great(t_list *tokens, void *data, unsigned int i);
void	check_less(t_list *tokens, void *data, unsigned int i);

#endif
