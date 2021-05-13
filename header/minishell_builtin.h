/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 22:25:41 by agautier          #+#    #+#             */
/*   Updated: 2021/04/19 21:31:017 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

typedef struct s_var
{
	char	*name;
	char	*equal;
	char	*value;
}	t_var;

unsigned char	builtin_echo(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_cd(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_pwd(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_env(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_export(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_unset(t_token *cmd, t_list **env, t_err *err);
unsigned char	builtin_exit(t_token *cmd, t_list **env, t_err *err);

/*
**	exec.c
*/

char	is_builtin(t_token *token, t_fd *fd, t_list *env, t_err *err);

/*
**	var.c
*/

t_var	*var_init(char *name, char *equal, char *value);
void	var_destroy(void *data);
char	*get_var_name(char *var);
char	*get_var_equal(char *var);
char	*get_var_value(char *var);

#endif
