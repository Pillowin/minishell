/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:08:16 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 15:13:454 byggieteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
// # include <sys/ioctl.h>
# include "libft.h"
# include "ft_list.h"
# include "ft_btree.h"

# define DEFAULT_PROMPT	"\e[35mmashashell>\e[39m"

# define FAILURE		0
# define SUCCESS		1
# define DONE			2

# define BUF_SIZE		1024
# define KEY_DEL		127
# define EOT			4
# define KEY_UP			"\x1B[A"
# define KEY_DOWN		"\x1B[B"

# define ARROW			-2
# define REAL			2

# define ERRNO_ERR		-2
# define CTRL_D			-1

enum
{
	IN = 0,
	OUT,
	REAL_IN,
	REAL_OUT
};

typedef pid_t	t_pid;
typedef struct	stat t_stat;
typedef struct	termios t_termios;
typedef struct	s_dlist t_dlist;

typedef struct	s_dlist
{
	void	*data;
	t_dlist	*next;
	t_dlist	*prev;
}				t_dlist;

typedef enum e_err_code
{
	NONE = 0,
	MALLOC,
	OPEN,
	CLOSE,
	MULTILINE_QUOTE,
	MULTILINE_DQUOTE,
	MULTILINE_BSLASH,
	SYNTAX_SEMI,
	SYNTAX_PIPE,
	SYNTAX_DGREAT,
	SYNTAX_GREAT,
	SYNTAX_LESS,
	HOME_NOT_SET,
	OLDPWD_NOT_SET,
	TOO_MANY_ARG,
	NOT_FOUND,
	NO_SUCH_FILE,
	IS_A_DIR,
	PERM,
	EXPORT,
	ERR_NO
}	t_err_code;

typedef struct	s_err
{
	t_list			**gc;
	char			**message;
	unsigned char	code;
	char			*cmd_name;
}				t_err;

typedef struct	s_fd
{
	int		redirs[4];
	int		pipes[4];
	char	is_forked;
	char	is_child;
	char	is_dad_pipe;
	t_pid	pid;
}	t_fd;

typedef struct	s_fd_env_err
{
	t_fd	*fd;
	t_list	*env;
	t_err	*err;
}				t_fd_env_err;

typedef struct	s_sig_param
{
	t_list	*env;
	t_err	*err;
}				t_sig_param;

typedef struct	s_tc_cmds
{
	t_dlist		*cmds;
	t_dlist		*cpy;
}				t_tc_cmds;

# include "minishell_lexer.h"
# include "minishell_parser.h"
# include "minishell_expansion.h"
# include "minishell_builtin.h"

unsigned short int	g_exit_status;

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **));

/*
**	gc_utils.c
*/
void	gc_list_push_back(t_list **begin_list, void *data, t_list **gc);
void	gc_list_clear(t_list *begin_list, void (*free_fct)(void **), t_list **gc);
void	gc_list_remove_var(t_list **begin_list, void *data_ref, t_list **gc);

/*
**	utils.c
*/

int		ft_is_end_word(char c);
int		ft_is_token(char c);
int		is_tok_type(t_token *data, void *type);
int		my_strdup(char ***strs, size_t size, char *str);
int		my_calloc(size_t count, size_t size, void **ptr);
size_t	ft_strslen(char **strs);
// char	**ft_strsdup(char **source);
int		is_var(void *data, void *ref);
char	is_name(char *word, char delimiter);
t_dlist	*gc_create_delem(t_list **gc, void *data);
void	gc_dlist_push_back(t_list **gc, t_dlist **begin_list, void *data);
int		ft_putchar(int c);
t_dlist	*dlst_last(t_dlist *dlist);
void	waitall();
char	tab_init(char **s1, char **s2, char **s3, t_list **gc);


/*
**	free.c
*/

void	ft_free_tab(void **data);
void	ft_lstdel(void **list);

/*
**	error.c
*/

void	err_init(char **err_msg);
void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **));

/*
**	env.c
*/

t_list	*insert_env(t_list **env, t_var v, t_list **gc);
t_list	*update_env(t_list **env, char *name, char *value, t_list **gc);
t_list	*env_init(char **envp, t_list **gc);
char	**env_to_tab(t_list *env);

/*
**	redir.c
*/

char	redir_init(t_token *token, int (*redirs)[4], t_err *err);
char	redir_destroy(int type, int (*redirs)[4]);

/*
**	pipe.c
*/

char	pipe_init(t_fd *fd);
char	pipe_destroy(t_fd *fd);

/*
**	prompt.c
*/

// char	prompt(t_list **env, t_list **gc);
void	prompt(void);


/*
**	binary.c
*/

char	*binary_absolute_path(t_token *token, t_err *err);
char	*binary_not_a_path(t_token *token, t_stat *buf, t_list *env, t_err *err);
char	*binary_relative_path(t_token *token, t_err *err);
// char	binary_exec(t_token *token, char *path, t_fd *fd, t_list *env);
char	binary_exec(t_token *token, char *path, t_fd *fd, t_list *env, t_err *err);

/*
**	exec.c
*/

char	exec(t_btree *tree, t_list *env, t_err *err);

/*
**	signal.c
*/

void	signal_init(void);

/*
**	main.c
*/

void	minishell(t_list *env, t_err *err);

/*
**	termcap
*/

t_tc_cmds 		*tc_cmds_init(t_list **gc);
char			tc_init(t_termios *termios);
char			tc_destroy(t_termios *termios);
int				tc_read(t_tc_cmds *tc_cmds, char **buf, t_list **gc);

char			tc_up(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **gc);
char			tc_down(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **gc);
void			tc_del(char **buf, unsigned int *i);
unsigned int	tc_eol(t_dlist **curr_cpy, char **buf, unsigned int *i);
int				tc_dispatch(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **gc);

/*
**	minishell.c
*/

void	minishell(t_list *env, t_err *err);

#endif
