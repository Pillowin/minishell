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
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_list.h"
# include "ft_btree.h"

# define DEFAULT_PROMPT	"\e[35mprompt>\e[39m"

# define SUCCESS		1
# define FAILURE		0

# define IN			0
# define OUT		1
# define REAL_IN	2
# define REAL_OUT	3



typedef struct stat t_stat;
typedef pid_t t_pid;

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

# include "minishell_lexer.h"
# include "minishell_parser.h"
# include "minishell_expansion.h"
# include "minishell_builtin.h"

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **));

/*
**	utils.c
*/

int		ft_is_end_word(char c);
int		ft_is_token(char c);
int		is_tok_type(t_token *data, void *type);
int		my_strdup(char ***strs, size_t size, char *str);
int		my_calloc(size_t count, size_t size, void **ptr);
size_t	ft_strslen(char **strs);
char	**ft_strsdup(char **source);
int		is_var(void *data, void *ref);
char	is_name(char *word, char delimiter);

/*
**	free.c
*/

void	ft_free_tab(void **data);
void	ft_lstdel(void **list);

void	exec(t_btree *tree, t_list *env);

/*
**	error.c
*/
void	err_init(char **err_msg);
void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **));

/*
**	env.c
*/
t_list	*env_init(char **envp);
char	**env_to_tab(t_list *env);

/*
**	redir.c
*/

void	redir_init(t_token *token, int (*fildes)[4]);
void	redir_destroy(int (*fildes)[4]);

/*
**	prompt.c
*/
char	prompt(t_list **env);

#endif
