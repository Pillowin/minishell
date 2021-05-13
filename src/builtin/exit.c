/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:01:31 by agautier          #+#    #+#             */
/*   Updated: 2021/05/12 15:26:10 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	builtin_exit(t_token *cmd, t_list **env, t_err *err)
{
	// TODO:
	(void)cmd;
	(void)env;
	(void)err;
	exit(EXIT_SUCCESS);
}
