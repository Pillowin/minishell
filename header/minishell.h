/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:08:16 by agautier          #+#    #+#             */
/*   Updated: 2021/03/16 19:02:03 by agautier         ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_list.h"
# include "ft_btree.h"

# include "minishell_lexer.h"
# include "minishell_parser.h"

#endif
