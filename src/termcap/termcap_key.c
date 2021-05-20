/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:58:24 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 22:01:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Select previous command in history
*/
char			tc_up(t_dlist **curr_cpy, char **buf, unsigned int *i
						, t_list **gc)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->prev)
	{
		gc_free(gc, (void **)&((*curr_cpy)->data));
		(*curr_cpy)->data = ft_strdup((*buf));
		if (!((*curr_cpy)->data))
			return (FAILURE);
		gc_register(gc, (*curr_cpy)->data);
		*curr_cpy = (*curr_cpy)->prev;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);
		ft_strncpy(*buf, (*curr_cpy)->data, BUF_SIZE);
		ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);
		write(STDIN_FILENO, (*buf), ft_strlen(*buf));
		*i = ft_strlen(*buf);
	}
	return (SUCCESS);
}

/*
**	Select next command in history
*/
char			tc_down(t_dlist **curr_cpy, char **buf, unsigned int *i
						, t_list **gc)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->next)
	{
		gc_free(gc, (void **)&((*curr_cpy)->data));
		(*curr_cpy)->data = ft_strdup(*buf);
		if (!((*curr_cpy)->data))
			return (FAILURE);
		gc_register(gc, (*curr_cpy)->data);
		*curr_cpy = (*curr_cpy)->next;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);
		ft_strncpy(*buf, (*curr_cpy)->data, BUF_SIZE);
		ft_putstr_fd(DEFAULT_PROMPT, STDOUT_FILENO);
		write(STDIN_FILENO, (*buf), ft_strlen(*buf));
		*i = ft_strlen(*buf);
	}
	return (SUCCESS);
}

/*
**	Remove prev printed char
*/
void			tc_del(char **buf, unsigned int *i)
{
	if (!(*i))
		return ;
	tputs(tgetstr("le", NULL), 1, &ft_putchar);
	tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	(*buf)[(*i)] = '\0';
	*i -= 1;
	(*buf)[(*i)] = '\0';
}

/*
**	Add buf to lists and go to parser
*/
unsigned int	tc_eol(t_dlist **curr_cpy, char **buf, unsigned int *i)
{
	unsigned int	index;

	(*buf)[*i] = '\0';
	index = 0;
	while ((*curr_cpy) && (*curr_cpy)->prev)
	{
		(*curr_cpy) = (*curr_cpy)->prev;
		index++;
	}
	return (index);
}

/*
**	Interpret key pressed
*/
int				tc_dispatch(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **gc)
{
	if (!ft_strncmp(&((*buf)[*i]), KEY_UP, 3))
	{
		if (!tc_up(curr_cpy, buf, i, gc))
			return (ARROW);
	}
	else if (!ft_strncmp(&((*buf)[*i]), KEY_DOWN, 3))
	{
		if (!tc_down(curr_cpy, buf, i, gc))
			return (ARROW);
	}
	else if ((*buf)[*i] == KEY_DEL)
		tc_del(buf, i);
	else if (ft_isprint((*buf)[*i]))
	{
		ft_putchar_fd((*buf)[*i], STDOUT_FILENO);
		*i += 1;
	}
	else if ((*buf)[*i] == '\n')
		return (tc_eol(curr_cpy, buf, i));
	else
		ft_strncpy(&((*buf)[*i]), "", 3);
	return (-1);
}
