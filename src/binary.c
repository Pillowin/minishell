/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:42:27 by agautier          #+#    #+#             */
/*   Updated: 2021/05/09 17:19:24 by agautier         ###   ########.fr       */
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
		return (error(err, MALLOC, NULL, NULL));	// TODO: error ?
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
		return (error(err, ERRNO, NULL, NULL));
	tmp = ft_strjoin(path, "/");
	ft_free((void **)&path);
	if (!tmp)
		return (error(err, MALLOC, NULL, NULL));// TODO: free path
	path = ft_strjoin(tmp, token->data[0]);
	ft_free((void **)&tmp);
	if (!path)
		return (error(err, MALLOC, NULL, NULL)); // TODO: free path et tmp
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
	
	tmp = ft_list_find(env, (void *)"PATH", &is_var);
	if (!tmp)
	{
		fprintf(stderr, "Not found error\n");
		return (error(err, NOT_FOUND, NULL, NULL));
	}
	tmp = ((t_var *)((t_list *)tmp)->data)->value;
	paths = ft_split(tmp, ':');	// 
	if (!paths)
		return (error(err, MALLOC, NULL, NULL));
	i = 0;
	while (paths[i])
	{
		path = paths[i];
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			return (error(err, MALLOC, (void **)paths, &ft_free_tab));
		path = ft_strjoin(tmp, token->data[0]);
		ft_free((void **)&tmp);
		if (!path)
			return (error(err, MALLOC, NULL, NULL));
		if (stat(path, buf) == 0)	// TODO: verif stat ?
			break;
		ft_free((void **)&path);
		i++;
	}
	if (!paths[i])
	{
		fprintf(stderr, "Not found error\n");
		return (error(err, NOT_FOUND, (void **)paths, &ft_free_tab));
	}
	path = ft_strdup(path);
	if (!path)
		return (error(err, MALLOC, NULL, NULL));
	ft_free_tab((void **)paths);
	return (path);
}

/*
**
*/

char	binary_exec(t_token *token, char *path, t_fd *fd, t_list *env, t_err *err)
{
	char	**envp;
	int		status;
	t_stat	buf;
	t_pid	pid;



	if (stat(path, &buf) != 0)
	{
		fprintf(stderr, "No such file error\n");
		return ((long)error(err, NO_SUCH_FILE, NULL, NULL));
	}
	if (buf.st_mode & S_IFDIR)
		return ((long)error(err, IS_A_DIR, NULL, NULL));
	else if (!(buf.st_mode & S_IXUSR))
		return ((long)error(err, PERM, NULL, NULL));
	envp = env_to_tab(env);
	if (!envp)
		return (FAILURE);
	if (!(fd->is_forked) || !(fd->is_child))
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		else if (!pid)	// si pid = 0 ca veut dire qu'on est dans l'enfant
		{
			if (execve(path, token->data, envp) == -1)
				return (FAILURE);
		}
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
