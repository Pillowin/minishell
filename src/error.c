/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:17:44 by agautier          #+#    #+#             */
/*   Updated: 2021/05/09 17:17:44 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

void	err_init(char **err_msg)
{
	err_msg[NONE] = "No error.";

	err_msg[MALLOC] = "Memory allocation failed.";	// TODO: multiply for different case // TODO: useless : use errno
	err_msg[OPEN] = "Cannot open";
	err_msg[CLOSE] = "Cannot close";

	err_msg[MULTILINE_QUOTE] = "minishell: Undefined case multiline quote command.";
	err_msg[MULTILINE_DQUOTE] = "minishell: Undefined case multiline double quote command.";
	err_msg[MULTILINE_BSLASH] = "minishell: Undefined case multiline back slash command.";
	err_msg[SYNTAX_SEMI] = "minishell: syntax error near unexpected token `;'";
	err_msg[SYNTAX_PIPE] = "minishell: syntax error near unexpected token `|'";
	err_msg[SYNTAX_DGREAT] = "minishell: syntax error near unexpected token `>>'";
	err_msg[SYNTAX_GREAT] = "minishell: syntax error near unexpected token `>'";
	err_msg[SYNTAX_LESS] = "minishell: syntax error near unexpected token `<'";

	err_msg[NOT_FOUND] = "command not found";
	err_msg[NO_SUCH_FILE] = "No such file or directory";

	err_msg[IS_A_DIR] = "is a directory";
	err_msg[PERM] = "Permission denied";
}

/*
**
*/

static void	set_exit_status(t_err_code code)
{
	if (!code || code == NONE)
		g_exit_status = 0;
	else if (code >= MULTILINE_QUOTE && code <= SYNTAX_LESS)
		g_exit_status = 2;
	else if (code == PERM || code == IS_A_DIR)
		g_exit_status = 126;
	else if (code == NOT_FOUND || code == NO_SUCH_FILE)
		g_exit_status = 127;
	else
		g_exit_status = EXIT_FAILURE;
}

/*
**
*/

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **))
{
	if (free_fct && ptr)
		free_fct(ptr);
	err->code = code;
	set_exit_status(code);
	return(NULL);
}
