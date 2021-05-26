/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:55:38 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 20:17:13 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/
t_tc_cmds	*tc_cmds_init(t_list **gc)
{
	t_tc_cmds	*tc_cmds;

	tc_cmds = (t_tc_cmds *)gc_calloc(gc, 1, sizeof(*tc_cmds));
	if (!tc_cmds)
		return (NULL);
	tc_cmds->cmds = NULL;
	tc_cmds->cpy = NULL;
	return (tc_cmds);
}

/*
**	Retrieve term type in env and disable canonic mode
*/
char	tc_init(struct termios *termios, unsigned int *i, int *index)
{
	char	*term_type;

	term_type = getenv("TERM");
	if (!term_type)
		term_type = "xterm-256color";
	tgetent(NULL, term_type);
	if (tcgetattr(STDIN_FILENO, termios) == -1)
		return (FAILURE);
	termios->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, 0, termios) == -1)
		return (FAILURE);
	*index = -1;
	*i = 0;
	return (SUCCESS);
}

/*
**	Reset canonic mode
*/
char	tc_destroy(struct termios *termios)
{
	termios->c_lflag |= (ICANON ^ ECHO);
	if (tcsetattr(STDIN_FILENO, 0, termios) == -1)
		return (ERRNO_ERR);
	return (CTRL_D);
}
