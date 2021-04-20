/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:01:31 by agautier          #+#    #+#             */
/*   Updated: 2021/04/20 21:24:10 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	builtin_exit(t_token *cmd, int fd, t_list **env)
{
	// TODO:
	(void)cmd;
	(void)fd;
	(void)env;
	exit(EXIT_SUCCESS);
}
