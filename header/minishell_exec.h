/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 12:18:48 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

typedef pid_t		t_pid;
typedef struct stat	t_stat;	// TODO:

enum
{
	IN = 0,
	OUT,
	REAL_IN,
	REAL_OUT
};

typedef struct s_fd
{
	int		redirs[4];
	int		pipes[4];
	char	is_forked;
	char	is_child;
	char	is_dad_pipe;
	t_pid	pid;
}	t_fd;

typedef struct s_fd_env_err
{
	t_fd	*fd;
	t_list	**env;
	t_err	*err;
}	t_fd_env_err;

/*
**	redir.c
*/
char	redir_init(t_token *token, int (*redirs)[4], t_err *err);
char	redir_destroy(int type, int (*redirs)[4], t_err *err);

/*
**	pipe.c
*/
char	pipe_init(t_fd *fd);
char	pipe_destroy(t_fd *fd);

/*
**	binary.c
*/
char	*binary_absolute_path(t_token *token, t_err *err);
char	*binary_not_a_path(t_token *token, t_stat *buf, t_list *env,
			t_err *err);
char	*binary_relative_path(t_token *token, t_err *err);
char	binary_exec(t_token *token, char *path, t_fd_env_err *fee);

/*
**	exec.c
*/
char	exec(t_btree *tree, t_list **env, t_err *err);

#endif
