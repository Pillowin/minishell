/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_termcap.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 12:16:00 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TERMCAP_H
# define MINISHELL_TERMCAP_H

# define BUF_SIZE		1024
# define KEY_DEL		127
# define EOT			4
# define KEY_UP			"\x1B[A"
# define KEY_DOWN		"\x1B[B"

# define ARROW			-2
# define REAL			2

# define ERRNO_ERR		-2
# define CTRL_D			-1

typedef struct termios	t_termios;	// TODO:

typedef struct s_tc_cmds
{
	t_dlist		*cmds;
	t_dlist		*cpy;
}	t_tc_cmds;

/*
**	termcap.c
*/
t_tc_cmds		*tc_cmds_init(t_list **gc);
char			tc_init(t_termios *termios);
char			tc_destroy(t_termios *termios);
int				tc_read(t_tc_cmds *tc_cmds, char **buf, t_list **gc);

/*
**	termcap_key.c
*/
char			tc_up(t_dlist **curr_cpy, char **buf, unsigned int *i,
					t_list **gc);
char			tc_down(t_dlist **curr_cpy, char **buf, unsigned int *i,
					t_list **gc);
void			tc_del(char **buf, unsigned int *i);
unsigned int	tc_eol(t_dlist **curr_cpy, char **buf, unsigned int *i);
int				tc_dispatch(t_dlist **curr_cpy, char **buf, unsigned int *i,
					t_list **gc);

#endif
