/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmamaqquig <mmamaqquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:49:04 by agautier          #+#    #+#             */
/*   Updated: 2021/05/11 15:05:04 by mmamaqquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Select previous command in history
*/

char			tc_up(t_dlist **curr_cpy, char **buf, unsigned int *i
						, t_list **env)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->prev)
	{
		ft_free((void *)&((*curr_cpy)->data));
		(*curr_cpy)->data = ft_strdup((*buf));
		if (!((*curr_cpy)->data))
			return (FAILURE);
		*curr_cpy = (*curr_cpy)->prev;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);
		ft_strncpy(*buf, (*curr_cpy)->data, BUF_SIZE);
		if (!prompt(env))
			return (FAILURE);
		write(STDIN_FILENO, (*buf), ft_strlen(*buf));
		*i = ft_strlen(*buf);
	}
	return (SUCCESS);
}

/*
**	Select next command in history
*/

char			tc_down(t_dlist **curr_cpy, char **buf, unsigned int *i
						, t_list **env)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->next)
	{
		ft_free((void *)&((*curr_cpy)->data));
		(*curr_cpy)->data = ft_strdup(*buf);
		if (!((*curr_cpy)->data))
			return (FAILURE);
		*curr_cpy = (*curr_cpy)->next;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);
		ft_strncpy(*buf, (*curr_cpy)->data, BUF_SIZE);
		if (!prompt(env))
			return (FAILURE);
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

int				tc_dispatch(t_dlist **curr_cpy, char **buf, t_list **env
							, unsigned int *i)
{
	// if (*i > 1 && !ft_strncmp(&((*buf)[*i - 1]), "^C", 2))
	// {
	// 	fprintf(stderr, "ctrl _ c bg\n");
		// fprintf(stderr, "buf = %s\n", &(*buf)[*i]);
	// }
	if (!ft_strncmp(&((*buf)[*i]), KEY_UP, 3))
	{
		if (!tc_up(curr_cpy, buf, i, env))
			return (ARROW);
	}
	else if (!ft_strncmp(&((*buf)[*i]), KEY_DOWN, 3))
	{
		if (!tc_down(curr_cpy, buf, i, env))
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
