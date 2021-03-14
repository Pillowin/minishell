/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/03/14 19:55:40 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXER_H
# define MINISHELL_LEXER_H

typedef struct s_token
{
	enum
	{
		TOKEN_UNKNOW = 0,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_LESS,
		TOKEN_GREAT,
		TOKEN_DGREAT,
		TOKEN_SEMI,
		TOKEN_NEWLINE
	}	e_type;
	char	*data;
}	t_token;

typedef struct s_lexer
{
	char			*str;
	unsigned int	str_len;
	char			c;
	unsigned int	i;
}	t_lexer;

void	lexer(char *av);

t_lexer	*lexer_init(char *str);
void	lexer_advance(t_lexer *lexer, unsigned int len);
t_token	*lexer_advance_word(t_lexer *lexer);
t_token	*lexer_advance_current(t_lexer *lexer, int type);
void	lexer_skip_spaces(t_lexer *lexer);
t_token	*lexer_get_token(t_lexer *lexer);

t_token	*token_init(int type, char *data);
char	*token_type_to_str(int type);
void	token_print(t_token *token);

#endif
