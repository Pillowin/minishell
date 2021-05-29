/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:38:30 by agautier          #+#    #+#             */
/*   Updated: 2021/05/29 12:22:37 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Init error messages.
*/
void	err_init(char **err_msg)
{
	err_msg[NONE] = "No error.";
	err_msg[MULTILINE_QUOTE] = "Undefined case multiline quote command.";
	err_msg[MULTILINE_DQUOTE]
		= "Undefined case multiline double quote command.";
	err_msg[MULTILINE_BSLASH] = "Undefined case multiline back slash command.";
	err_msg[SYNTAX_SEMI] = "syntax error near unexpected token `;'";
	err_msg[SYNTAX_PIPE] = "syntax error near unexpected token `|'";
	err_msg[SYNTAX_DGREAT] = "syntax error near unexpected token `>>'";
	err_msg[SYNTAX_GREAT] = "syntax error near unexpected token `>'";
	err_msg[SYNTAX_LESS] = "syntax error near unexpected token `<'";
	err_msg[HOME_NOT_SET] = "« HOME » not set";
	err_msg[OLDPWD_NOT_SET] = "« OLDPWD » not set";
	err_msg[TOO_MANY_ARG] = "too many arguments";
	err_msg[CMD_NOT_FOUND] = "No such file or directory";
	err_msg[CMD_PERM] = "Permission denied";
	err_msg[NOT_FOUND] = "command not found";
	err_msg[NO_SUCH_FILE] = "No such file or directory";
	err_msg[IS_A_DIR] = "is a directory";
	err_msg[REDIR_DIR] = "is a directory";
	err_msg[PERM] = "Permission denied";
	err_msg[EXPORT] = "not a valid indentifier";
}

/*
**	Guess and set g_exit_status from error code.
*/
static void	set_exit_status(t_err_code code)
{
	if (!code)
		g_exit_status = 0;
	else if (code >= MULTILINE_QUOTE && code <= SYNTAX_LESS)
		g_exit_status = 2;
	else if (code == CMD_PERM || code == IS_A_DIR)
		g_exit_status = 126;
	else if (code == NOT_FOUND || code == CMD_NOT_FOUND)
		g_exit_status = 127;
	else if (code != NONE)
		g_exit_status = 1;
}

/*
**	Set error code and call free functions.
*/
void	*error(t_err *err, t_err_code code, void **ptr,
	void (*free_fct)(void **, t_list **))
{
	if (free_fct && ptr)
		free_fct(ptr, err->gc);
	err->code = code;
	if (code)
		set_exit_status(code);
	return (NULL);
}

/*
**	Print error message to STDERR_FILENO.
*/
void	perr_msg(char *cmd_name, char *arg, char *msg, t_list **gc)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1 || dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
	if (msg && cmd_name && arg)
		printf("minishell: %s: %s: %s\n", cmd_name, arg, msg);
	else if (msg && cmd_name)
		printf("minishell: %s: %s\n", cmd_name, msg);
	else
		printf("minishell: %s\n", msg);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
}
