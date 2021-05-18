/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:42:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/10 17:555:52 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
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
**
*/

char	*binary_relative_path(t_token *token, t_err *err)
{
	char	*path;
	void	*tmp;
	
	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	gc_register(err->gc, path);
	tmp = ft_strjoin(path, "/");
	gc_free(err->gc, (void **)&path);
	if (!tmp)
		return (NULL);
	gc_register(err->gc, tmp);
	path = ft_strjoin(tmp, token->data[0]);
	gc_free(err->gc, (void **)&tmp);
	if (!path)
		return (NULL);
	gc_register(err->gc, path);
	return (path);
}

/*
**
*/

char	*binary_not_a_path(t_token *token, t_stat *buf, t_list *env, t_err *err)
{
	unsigned int	i;
	char			**paths;
	char			*path;
	void			*tmp;
	
	tmp = ft_list_find(env, "PATH", &is_var);
	if (!tmp)
		return (error(err, NOT_FOUND, NULL, NULL));
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
	
	i = 0;
	while (paths[i])
	{
		path = paths[i];
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			return (error(err, FATAL, NULL, NULL));
		gc_register(err->gc, tmp);
		path = ft_strjoin(tmp, token->data[0]);
		gc_free(err->gc, (void **)&tmp);
		if (!path)
			return (error(err, FATAL, NULL, NULL));
		gc_register(err->gc, path);
		if (stat(path, buf) == 0)
			break;
		gc_free(err->gc, (void **)&path);
		i++;
	}
	if (!paths[i])
		return (error(err, NOT_FOUND, (void **)paths, &gc_free_tab));
	path = ft_strdup(path);
	if (!path)
		return (error(err, FATAL, NULL, NULL));
	gc_register(err->gc, path);
	gc_free_tab((void **)paths, err->gc);
	return (path);
}

/*
**
*/

char	binary_exec(t_token *token, char *path, t_fd_env_err *fee)
{
	char	**envp;
	int		status;
	t_stat	buf;
	t_pid	pid;

	if (stat(path, &buf) != 0)
		return ((long)error(fee->err, NO_SUCH_FILE, NULL, NULL));
	if (buf.st_mode & S_IFDIR)
		return ((long)error(fee->err, IS_A_DIR, NULL, NULL));
	else if (!(buf.st_mode & S_IXUSR))
		return ((long)error(fee->err, PERM, NULL, NULL));
	envp = env_to_tab(*(fee->env), fee->err->gc);
	if (!envp)
		return ((long)error(fee->err, FATAL, NULL, NULL));
	if (!(fee->fd->is_forked) || !(fee->fd->is_child))
	{
		pid = fork();
		if (pid == -1)
			return ((long)error(fee->err, FATAL, NULL, NULL));
		else if (!pid)
			if (execve(path, token->data, envp) == -1)
				return ((long)error(fee->err, FATAL, NULL, NULL));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			g_exit_status = WEXITSTATUS(status);
			return (SUCCESS);
		}
		return (SUCCESS);
	}
	execve(path, token->data, envp);
	return (FAILURE);
}
