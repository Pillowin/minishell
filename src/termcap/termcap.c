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
**	Init input read
*/
char	*tc_read_init(t_tc_cmds *tc_cmds, t_dlist **curr, t_dlist **curr_cpy
						, t_list **gc)
{
	char	*buf;
	char	*empty;

	buf = (char *)gc_calloc(gc, BUF_SIZE + 3 + 1, sizeof(*buf));
	if (!buf)
		return (NULL);
	*curr = dlst_last(tc_cmds->cmds);
	if (!(*curr) || ((char *)((*curr)->data))[0])
	{
		empty = ft_strdup("");
		if (!empty)
			return (NULL);
		gc_register(gc, empty);
		gc_dlist_push_back(gc, &(tc_cmds->cpy), empty);
		empty = ft_strdup("");
		if (!empty)
			return (NULL);
		gc_register(gc, empty);
		gc_dlist_push_back(gc, &(tc_cmds->cmds), empty);
	}
	*curr_cpy = dlst_last(tc_cmds->cpy);
	return (buf);
}

/*
**
*/
static char	tc_read_destroy_2(t_dlist *cmds, char **buf, t_dlist *cpy
								, t_list **gc)
{
	gc_register(gc, cpy->data);
	cmds = dlst_last(cmds);
	gc_free(gc, (void **)&(cmds->data));
	cmds->data = ft_strdup(*buf);
	if (!(cmds->data))
		return (FAILURE);
	gc_register(gc, cmds->data);
	cpy = dlst_last(cpy);
	gc_free(gc, (void **)&(cpy->data));
	cpy->data = ft_strdup(cmds->data);
	if (!(cpy->data))
		return (FAILURE);
	gc_register(gc, cpy->data);
	return (SUCCESS);
}

/*
**	Add buff to list and go to parser
*/
char	tc_read_destroy(t_tc_cmds *tc_cmds, char **buf, unsigned int index
						, t_list **gc)
{
	t_dlist	*cmds;
	t_dlist	*cpy;

	cmds = tc_cmds->cmds;
	cpy = tc_cmds->cpy;
	while (index)
	{
		if (cmds->next)
			cmds = cmds->next;
		if (cpy->next)
			cpy = cpy->next;
		index--;
	}
	gc_free(gc, (void **)&(cpy->data));
	cpy->data = ft_strdup(cmds->data);
	if (!(cpy->data))
		return (FAILURE);
	if (!tc_read_destroy_2(cmds, buf, cpy, gc))
		return (FAILURE);
	return (SUCCESS);
}

/*
**
*/
static char	handle_ctrl_c(char **buf, struct termios *termios, unsigned int *i)
{
	if (g_exit_status & 0x0F00)
	{
		*i = (*buf)[*i];
		ft_strncpy(*buf, "", BUF_SIZE);
		if (ft_isprint(*i))
		{
			(*buf)[0] = *i;
			ft_putchar_fd(*i, STDOUT_FILENO);
		}
		if (*i == EOT || (*buf)[0] == EOT)
			return (tc_destroy(termios));
		*i = ft_isprint(*i);
		g_exit_status &= 0x00FF;
		return (SUCCESS);
	}
	if ((*buf)[*i] == EOT && !*i)
		return (tc_destroy(termios));
	return (FAILURE);
}

/*
**	Read input from STDIN
*/
int	tc_read(t_tc_cmds *tc_cmds, char **buf, t_list **gc)
{
	struct termios	termios;
	t_dlist			*curr;
	t_dlist			*curr_cpy;
	unsigned int	i;
	int				index;

	*buf = tc_read_init(tc_cmds, &curr, &curr_cpy, gc);
	if (!(*buf) || !tc_init(&termios, &i, &index))
		return (ERRNO_ERR);
	while (i < BUF_SIZE && read(STDIN_FILENO, &((*buf)[i]), BUF_SIZE - i))
	{
		index = handle_ctrl_c(buf, &termios, &i);
		if (index < 0)
			return (index);
		else if (index)
			continue ;
		index = tc_dispatch(&curr_cpy, buf, &i, gc);
		if (index == ARROW)
			return (ERRNO_ERR);
		else if (index != -1)
			break ;
	}
	if (!tc_read_destroy(tc_cmds, buf, index, gc) || !tc_destroy(&termios))
		return (ERRNO_ERR);
	return (i);
}
