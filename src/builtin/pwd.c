/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:19:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 18:333:04 byagattierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Print current working directory.
*/

unsigned char	builtin_pwd(t_token *cmd, t_list **env, t_err *err)
{
	char *buf;

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
