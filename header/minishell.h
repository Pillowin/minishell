/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:09:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 20:24:27 by agautier         ###   ########.fr       */
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
# include "libft.h"
# include "ft_list.h"
# include "ft_btree.h"

# include "minishell_error.h"
# include "minishell_env.h"
# include "minishell_signal.h"
# include "minishell_termcap.h"
# include "minishell_lexer.h"
# include "minishell_parser.h"
# include "minishell_expansion.h"
# include "minishell_exec.h"
# include "minishell_builtin.h"
# include "minishell_utils.h"

# define DEFAULT_PROMPT	"\e[35mminishell>\e[39m"

unsigned short			g_exit_status;
typedef struct s_dlist	t_dlist;

typedef struct s_dlist
{
	void	*data;
	t_dlist	*next;
	t_dlist	*prev;
}	t_dlist;

/*
**	minishell.c
*/
void	minishell(t_list **env, t_err *err);

#endif
