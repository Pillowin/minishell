/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:17:44 by agautier          #+#    #+#             */
/*   Updated: 2021/04/22 12:18:17 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
void	err_init(char **err_msg)
{
	err_msg[NONE] = "No error\n";
	err_msg[MALLOC] = "Memory allocation failed.\n";
	err_msg[MULTILINE_QUOTE] = "Undefined case : multiline quote command.\n";
	err_msg[MULTILINE_DQUOTE] = "Undefined case : multiline double quote command.\n";
	err_msg[MULTILINE_BSLASH] = "Undefined case : multiline back slash command.\n";
	err_msg[SYNTAX_SEMI] = "bash: syntax error near unexpected token `;'\n";
	err_msg[SYNTAX_PIPE] = "bash: syntax error near unexpected token `|'\n";
	err_msg[SYNTAX_DGREAT] = "bash: syntax error near unexpected token `>>'\n";
	err_msg[SYNTAX_GREAT] = "bash: syntax error near unexpected token `>'\n";
	err_msg[SYNTAX_LESS] = "bash: syntax error near unexpected token `<'\n";
}

/*
**
*/
void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **))
{
	if (free_fct && ptr)
		free_fct(ptr);
	ft_putstr_fd(err->message[code], STDERR_FILENO);
	// set exit_status
		// TODO:
	return(NULL);
}
