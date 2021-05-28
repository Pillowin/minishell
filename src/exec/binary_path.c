/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:20:16 by agautier          #+#    #+#             */
/*   Updated: 2021/05/28 17:38:41 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Create path from token when path is absolute.
*/
char	*binary_absolute_path(t_token *token, t_err *err)
{
	char	*path;

	path = ft_strdup(token->data[0]);
	if (!path)
		return (NULL);
	gc_register(err->gc, path);
	return (path);
}

/*
**	Create path from token when path is relative.
*/
char	*binary_relative_path(t_token *token, t_err *err)
{
	char	*path;
	void	*tmp;

	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	gc_register(err->gc, path);
	tmp = gc_strjoin(path, "/", err->gc);
	gc_free(err->gc, (void **)&path);
	if (!tmp)
		return (NULL);
	path = gc_strjoin(tmp, token->data[0], err->gc);
	gc_free(err->gc, (void **)&tmp);
	if (!path)
		return (NULL);
	return (path);
}

/*
**	Find $PATH in environment.
*/
static char	**fetch_path(t_list *env, t_err *err)
{
	unsigned int	i;
	char			**paths;
	void			*tmp;

	tmp = ft_list_find(env, "PATH", &is_var);
	if (!tmp)
		return (error(err, CMD_NOT_FOUND, NULL, NULL));
	tmp = ((t_var *)((t_list *)tmp)->data)->value;
	paths = ft_split(tmp, ':');
	if (!paths)
		return (error(err, FATAL, NULL, NULL));
	gc_register(err->gc, paths);
	i = 0;
	while (paths[i])
	{
		gc_register(err->gc, paths[i]);
		i++;
	}
	return (paths);
}

/*
**	
*/
static char	*check_paths(t_token *token, char **paths, struct stat *buf,
							t_err *err)
{
	unsigned int	i;
	char			*path;
	void			*tmp;

	path = NULL;
	i = 0;
	while (paths[i])
	{
		path = paths[i];
		tmp = gc_strjoin(path, "/", err->gc);
		if (!tmp)
			return (error(err, FATAL, NULL, NULL));
		path = gc_strjoin(tmp, token->data[0], err->gc);
		gc_free(err->gc, (void **)&tmp);
		if (!path)
			return (error(err, FATAL, NULL, NULL));
		if (stat(path, buf) == 0)
			break ;
		gc_free(err->gc, (void **)&path);
		i++;
	}
	if (!paths[i])
		return (error(err, NOT_FOUND, (void **)paths, &gc_free_tab));
	return (path);
}

/*
**	Create path from token when PATH var is needed.
*/
char	*binary_not_a_path(t_token *token, struct stat *buf, t_list *env,
							t_err *err)
{
	char	**paths;
	char	*path;

	paths = fetch_path(env, err);
	if (!paths)
		return (FAILURE);
	path = check_paths(token, paths, buf, err);
	if (!path)
		return (FAILURE);
	path = gc_strdup(path, err->gc);
	if (!path)
		return (error(err, FATAL, NULL, NULL));
	gc_free_tab((void **)paths, err->gc);
	return (path);
}
