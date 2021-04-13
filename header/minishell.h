/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:08:16 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 15:13:444 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**		-- The grammar symbols --
**
**	WORD
**	NEWLINE
**	PIPE :		|
**	LESS :		<
**	GREAT :		>
**	DGREAT :	>>
**	SEMI :		;
**
**	QUOTE :		'
**	DQUOTE :	"
**	BSLAH :		\
**
**		-- The Grammar --
**
**	program        : command NEWLINE
**	               |         NEWLINE
**	               ;
**	command        : simple_command separator command
**	               | simple_command SEMI
**	               | simple_command
**	               ;
**	simple_command : cmd_prefix WORD cmd_suffix
**	               | cmd_prefix WORD
**	               | cmd_prefix
**	               |            WORD cmd_suffix
**	               |            WORD
**	               ;
**	cmd_prefix     : io_file cmd_prefix
**	               | io_file
**	               ;
**	word           : WORD
**	               ;
**	cmd_suffix     : io_file cmd_suffix
**	               | io_file
**	               | WORD    cmd_suffix
**	               | WORD
**	               ;
**	io_file        : LESS   WORD
**	               | GREAT  WORD
**	               | DGREAT WORD
**	               ;
**	separator      : PIPE
**	               | SEMI
**	               ;
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_list.h"
# include "ft_btree.h"

typedef struct s_err t_err;

# include "minishell_lexer.h"
# include "minishell_parser.h"
# include "minishell_expansion.h"

# define SUCCESS		1
# define FAILURE		0

typedef enum
{
	NONE = 0,
	MALLOC,
	MULTILINE_QUOTE,
	MULTILINE_DQUOTE,
	MULTILINE_BSLASH,
	SYNTAX_SEMI,
	SYNTAX_PIPE,
	SYNTAX_DGREAT,
	SYNTAX_GREAT,
	SYNTAX_LESS
}	t_err_code;

typedef struct	s_err
{
	char**			message;
	unsigned char	status;
}				t_err;

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **));

/*
**	utils.c
*/

int	ft_is_end_word(char c);
int	ft_is_token(char c);
int	is_tok_type(t_token *data, void *type);
int	ft_strsdup(char ***strs, size_t size, char *str);
int	my_calloc(size_t count, size_t size, void **ptr);

/*
**	free.c
*/

void	ft_free_tab(void **data);
void	ft_lstdel(void **list);

#endif
