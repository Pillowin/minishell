/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:39:37 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 15:39:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Print current working directory.
*/
char	builtin_pwd(t_token *cmd, t_list **env, t_err *err)
{
	char	*buf;

	(void)cmd;
	(void)env;
	buf = getcwd(NULL, 0);
	if (!buf)
		return ((long)error(err, FATAL, NULL, NULL));
	gc_register(err->gc, buf);
	ft_putendl_fd(buf, STDOUT_FILENO);
	gc_free(err->gc, (void **)&buf);
	return (SUCCESS);
}
