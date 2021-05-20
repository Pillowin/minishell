/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:09:46 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 15:19:32 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

/*
**	builtins
*/
char	builtin_echo(t_token *cmd, t_list **env, t_err *err);
char	builtin_cd(t_token *cmd, t_list **env, t_err *err);
char	builtin_pwd(t_token *cmd, t_list **env, t_err *err);
char	builtin_env(t_token *cmd, t_list **env, t_err *err);
char	builtin_export(t_token *cmd, t_list **env, t_err *err);
char	builtin_unset(t_token *cmd, t_list **env, t_err *err);
char	builtin_exit(t_token *cmd, t_list **env, t_err *err);

#endif
