/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:53:45 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 21:43:42 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Find corresponding path based on first token data char.
*/
static char	*fetch_path(t_token *token, t_list **env, t_err *err)
{
	char		*path;
	struct stat	buf;

	path = NULL;
	if (token->data[0][0] == '/')
	{
		path = binary_absolute_path(token, err);
		if (!path)
			return (error(err, ERR_NO, NULL, NULL));
	}
	else if (token->data[0][0] == '.')
	{
		path = binary_relative_path(token, err);
		if (!path)
			return (error(err, ERR_NO, NULL, NULL));
	}
	else
	{
		path = binary_not_a_path(token, &buf, *env, err);
		if (!path)
			return (NULL);
	}
	return (path);
}

/*
**	Exec builtin or binary depending on the token name.
*/
char	exec_cmd(t_token *token, t_fd *fd, t_list **env, t_err *err)
{
	char			*path;
	int				ret;
	t_fd_env_err	*fee;

	fee = &((t_fd_env_err){fd, env, err});
	ret = is_builtin(token, fee->fd, fee->env, fee->err);
	if (!ret)
		return (FAILURE);
	else if (ret == DONE)
		return (SUCCESS);
	path = fetch_path(token, fee->env, fee->err);
	if (!binary_exec(token, path, fee))
	{
		gc_free(fee->err->gc, (void **)&path);
		return (FAILURE);
	}
	gc_free(fee->err->gc, (void **)&path);
	return (SUCCESS);
}
