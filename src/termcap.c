/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:09:37 by agautier          #+#    #+#             */
/*   Updated: 2021/05/04 22:444:77 byggieteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*dlst_last(t_dlist *dlist)
{
	while (dlist && dlist->next)
		dlist = dlist->next;
	return (dlist);
}

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
	return (SUCCESS);
}

/*
**
*/

// void	print_lsts(t_dlist *cmds, t_dlist *cpy)
// {
// 	printf("\n====================================================\n");
// 	while (cmds)
// 	{
// 		printf("cmds = %s\n", (char *)(cmds->data));
// 		cmds = cmds->next;
// 	}
// 	printf("\n");
// 	while (cpy)
// 	{
// 		printf("cpy = %s\n", (char *)(cpy->data));
// 		cpy = cpy->next;
// 	}
// 	printf("\n");

// }

/*
**
*/

char	*tc_read_init(t_dlist **cmds, t_dlist **cpy, t_dlist **curr, t_dlist **curr_cpy)
{
	char	*buf;

	buf = (char *)ft_calloc(BUF_SIZE + 3 + 1, sizeof(*buf));
	if (!buf)
		return (NULL);
	(*curr) = dlst_last(*cmds);
	if (!(*curr) || ((char *)((*curr)->data))[0])
	{
		ft_dlist_push_back(cpy, buf);
		ft_dlist_push_back(cmds, "");
	}
	*curr_cpy = dlst_last(*cpy);
	return (buf);
}

/*
**
*/

char	tc_read_destroy(t_dlist *cmds, t_dlist *cpy, char **buf, unsigned int index)
{
	char *data;
	
	while (index)
	{
		if (cmds->next)
			cmds = cmds->next;
		if (cpy->next)
			cpy = cpy->next;
		index--;
	}
	cpy->data = (char *)ft_calloc(BUF_SIZE, sizeof(char));
	if (!(cpy->data))
		return (FAILURE);
	ft_strncpy(cpy->data, cmds->data, BUF_SIZE);
	data = (char *)ft_calloc(BUF_SIZE, sizeof(*data));
	if (!(data))
		return (FAILURE);
	ft_strncpy(data, *buf, BUF_SIZE);
	cmds = dlst_last(cmds);
	cmds->data = data;
	cpy = dlst_last(cpy);
	cpy->data = (char *)ft_calloc(BUF_SIZE, sizeof(char));
	if (!(cpy->data))
		return (FAILURE);
	ft_strncpy(cpy->data, cmds->data, BUF_SIZE);
	return (SUCCESS);
}

/*
**	Read input from STDIN
*/

int	tc_read(t_dlist **cmds, t_dlist **cpy, char **buf, t_list **env)
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
	index = 0;
	i = 0;
	while (i < BUF_SIZE && read(STDIN_FILENO, &((*buf)[i]), BUF_SIZE))
	{
		if ((*buf)[i] == EOT && !i)
		{
			tc_destroy(&termios);
			return (-1);
		}
		index = tc_dispatch(&curr_cpy, buf, env, &i);
		if (index != -1)
			break ;
	}
	if (!tc_read_destroy(*cmds, *cpy, buf, index))
		return (-2);
	if (!tc_destroy(&termios))
		return (-2);
	return (i);
}
