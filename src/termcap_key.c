/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:49:04 by agautier          #+#    #+#             */
/*   Updated: 2021/05/06 18:06:15 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Select previous command in history
*/

void	tc_up(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **env)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->prev)
	{
		(*curr_cpy)->data = ft_strdup((*buf));	// ?????????????????????????????????
		*curr_cpy = (*curr_cpy)->prev;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);	// dl pour delete_line
		ft_strncpy((*buf), (*curr_cpy)->data, BUF_SIZE);
		prompt(env);	// TODO: check
		write(STDIN_FILENO, (*buf), ft_strlen((*buf)));
		*i = ft_strlen((*buf));
	}
}

/*
**	Select next command in history
*/

void	tc_down(t_dlist **curr_cpy, char **buf, unsigned int *i, t_list **env)
{
	ft_strncpy(&((*buf)[(*i)]), "", 3);
	if ((*curr_cpy)->next)
	{
		(*curr_cpy)->data = ft_strdup((*buf));	// TODO: free un jour  - really need to dup ?
		(*curr_cpy) = (*curr_cpy)->next;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar);	// dl pour delete_line
		ft_strncpy((*buf), (*curr_cpy)->data, BUF_SIZE);
		prompt(env);	// TODO: check
		write(STDIN_FILENO, (*buf), ft_strlen(*buf));
		(*i) = ft_strlen(*buf);
	}
}

/*
**	Remove prev printed char
*/

void	tc_del(char **buf, unsigned int *i)
{
	if (!(*i))
		return ;
	tputs(tgetstr("le", NULL), 1, &ft_putchar);	// le pour se déplacer à gauche
	tputs(tgetstr("dc", NULL), 1, &ft_putchar);	// dc pour delete next char
	(*buf)[(*i)] = '\0';
	*i -= 1;
	(*buf)[(*i)] = '\0';
}

/*
**	
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
**
*/

int	tc_dispatch(t_dlist **curr_cpy, char **buf, t_list **env, unsigned int *i)
{
	if (!ft_strncmp(&((*buf)[*i]), KEY_UP, 3))	// fleche du haut
		tc_up(curr_cpy, buf, i, env);
	else if (!ft_strncmp(&((*buf)[*i]), KEY_DOWN, 3))	// fleche du bas
		tc_down(curr_cpy, buf, i, env);
	else if ((*buf)[*i] == KEY_DEL)	// appui sur del
		tc_del(buf, i);
	else if (ft_isprint((*buf)[*i]))	// affichage du caractere standard
	{
		ft_putchar_fd((*buf)[*i], STDOUT_FILENO);
		*i += 1;
	}
	else if ((*buf)[*i] == '\n')	// stop la lecture car \n
		return (tc_eol(curr_cpy, buf, i));
	else
		ft_strncpy(&((*buf)[*i]), "", 2);
	return (-1);
}
