/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:09:46 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 12:10:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

/*
**	builtins
*/
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
char			is_builtin(t_token *token, t_fd *fd, t_list **env, t_err *err);

#endif
