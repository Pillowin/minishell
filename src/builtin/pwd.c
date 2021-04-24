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

unsigned char	builtin_pwd(t_token *cmd, t_list **env)
{
	char *buf;

	(void)cmd;	// TODO: ?
	(void)env;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (FAILURE);
	printf("%s\n", buf);
	ft_free((void **)&buf);
	return (SUCCESS);
}
