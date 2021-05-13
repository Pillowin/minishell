/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:54:22 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 22:01:34 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Retrieve term type in env and disable canonic mode
*/

char	tc_init(t_termios *termios)
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
	return (SUCCESS);
}

/*
**	Reset canonic mode
*/

char	tc_destroy(t_termios *termios)
{
	termios->c_lflag |= (ICANON ^ ECHO);
	if (tcsetattr(STDIN_FILENO, 0, termios) == -1)
		return (-2);
	return (-1);
}

/*
**	Init input read
*/

char	*tc_read_init(t_dlist **cmds, t_dlist **cpy, t_dlist **curr,
						t_dlist **curr_cpy)
{
	char	*buf;
	char	*empty;

	buf = (char *)ft_calloc(BUF_SIZE + 3 + 1, sizeof(*buf));
	if (!buf)
		return (NULL);
	(*curr) = dlst_last(*cmds);
	if (!(*curr) || ((char *)((*curr)->data))[0])
	{
		empty = ft_strdup("");
		if (!empty)
			return (NULL);
		ft_dlist_push_back(cpy, empty);
		empty = ft_strdup("");
		if (!empty)
			return (NULL);
		ft_dlist_push_back(cmds, empty);
	}
	*curr_cpy = dlst_last(*cpy);
	return (buf);
}

/*
**	Add buff to list and go to parser
*/

char	tc_read_destroy(t_dlist *cmds, t_dlist *cpy, char **buf
							, unsigned int index)
{
	while (index)
	{
		if (cmds->next)
			cmds = cmds->next;
		if (cpy->next)
			cpy = cpy->next;
		index--;
	}
	ft_free((void **)&(cpy->data));
	cpy->data = ft_strdup(cmds->data);
	if (!(cpy->data))
		return (FAILURE);
	cmds = dlst_last(cmds);
	ft_free((void **)&(cmds->data));
	cmds->data = ft_strdup(*buf);
	if (!(cmds->data))
		return (FAILURE);
	cpy = dlst_last(cpy);
	ft_free((void **)&(cpy->data));
	cpy->data = ft_strdup(cmds->data);
	if (!(cpy->data))
		return (FAILURE);
	return (SUCCESS);
}

/*
**	Read input from STDIN
*/

int		tc_read(t_dlist **cmds, t_dlist **cpy, char **buf, t_list **env)
{
	t_termios		termios;
	t_dlist			*curr;
	t_dlist			*curr_cpy;
	unsigned int	i;
	int				index;

	if (!tc_init(&termios))
		return (-2);
	*buf = tc_read_init(cmds, cpy, &curr, &curr_cpy);
	if (!(*buf))
		return (-2);
	index = -1;
	i = 0;
	while (i < BUF_SIZE && read(STDIN_FILENO, &((*buf)[i]), BUF_SIZE))
	{
		if (g_exit_status & 0xFF00)
		{
			i = (*buf)[i];
			ft_strncpy(*buf, "", BUF_SIZE);
			if (ft_isprint(i))
			{
				(*buf)[0] = i;
				ft_putchar_fd(i, STDOUT_FILENO);
			}
			if (i == EOT || (*buf)[0] == EOT)
				return (tc_destroy(&termios));
			if (ft_isprint(i))
				i = 1;
			else
				i = 0;
			g_exit_status &= 0x00FF;
			continue ;
		}
		if ((*buf)[i] == EOT && !i)
			return (tc_destroy(&termios));
		index = tc_dispatch(&curr_cpy, buf, env, &i);
		if (index == ARROW)
			return (-2);
		else if (index != -1)
			break ;
	}
	if (!tc_read_destroy(*cmds, *cpy, buf, index) || !tc_destroy(&termios))
		return (-2);
	return (i);
}
