/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:38:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/22 22:22:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// **
// */
// static void	my_btree_prefix(t_btree *root, t_list *env, void (*f)(void *, t_list *env))
// {
// 	if (!root)
// 		return ;
// 	f(root->item, env);
// 	my_btree_prefix(root->left, env, f);
// 	my_btree_prefix(root->right, env, f);
// }

/*
**
*/
void	binary_exec(t_token *token, t_list *env, char *path)
{
	char	**envp;
	t_stat	buf;
	t_pid	pid;

	if (stat(path, &buf) != 0)
	{
		printf("on return : %s\n", strerror(errno));
		return ;
	}
	if (buf.st_mode & S_IXUSR)
	{
		pid = fork();
		if (!pid)	// si pid = 0 ca veut dire qu'on est dans l'enfant
		{
			envp = env_to_tab(env);
			if (execve(path, token->data, envp) == -1)
				printf("err = %s\n", strerror(errno));
		}
		waitpid(pid, NULL, 0);
	}
}

// static int	cmp(void *data, void *ref)
// {
// 	if (!ft_strcmp(((t_var *)data)->name, ref))
// 		return (0);
// 	return (1);
// }

// /*
// **
// */
// static void	exec_cmd(t_token *token, t_list *env)
// {
// 	unsigned int	i;
// 	int				fd;
// 	char			*path;
// 	char			**paths;
// 	void			*tmp;
// 	t_stat			buf;
// 	const char		*builtin_names[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
// 	unsigned char	(*builtins[7])(t_token *cmd, int fd, t_list **env) = {
// 		&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export, &builtin_unset, &builtin_env, &builtin_exit};
// 	fd = STDOUT_FILENO;	// TODO:
// 	i = 0;
// 	while (i < 7)
// 	{
// 		if (!ft_strcmp(token->data[0], (char *)builtin_names[i]))
// 		{
// 			builtins[i](token, fd, &env);
// 			return ;
// 		}
// 		i++;
// 	}
// 	if (token->data[0][0] == '/')	// si path absolute		=> /bin/ls
// 	{
// 		path = ft_strdup(token->data[0]);
// 		if (!path)
// 			return ;	// TODO: error ?
// 	}
// 	else if (token->data[0][0] == '.')	// is path relative 	=> ../ls
// 	{
// 		path = getcwd(NULL, 0);
// 		if (!path)
// 			return ;	// TODO: error ?
// 		tmp = ft_strjoin(path, "/");
// 		ft_free((void **)&path);
// 		if (!tmp)
// 			return ;
// 		path = ft_strjoin(tmp, token->data[0]);
// 		ft_free((void **)&tmp);
// 		if (!path)
// 			return ;
// 	}
// 	else	// is not a path		=> ls
// 	{
// 		tmp = ft_list_find(env, (void *)"PATH", &cmp);
// 		if (!tmp)
// 			return ;
// 		tmp = ((t_var *)((t_list *)tmp)->data)->value;
// 		paths = ft_split(tmp, ':');	// 
// 		i = 0;
// 		while (paths[i])
// 		{
// 			path = paths[i];
// 			if (!path)
// 				return ;	// TODO: error ?
// 			tmp = ft_strjoin(path, "/");
// 			if (!tmp)
// 			{
// 				ft_free_tab((void **)paths);
// 				return ;
// 			}
// 			path = ft_strjoin(tmp, token->data[0]);
// 			ft_free((void **)&tmp);
// 			if (!path)
// 				return ;
// 			if (stat(path, &buf) == 0)
// 				break;
// 			ft_free((void **)&path);
// 			i++;
// 		}
// 		if (!paths[i])
// 		{
// 			printf("command not found\n");
// 			ft_free_tab((void **)paths);
// 			return ;	// TODO: command not found
// 		}
// 		path = ft_strdup(path);
// 		ft_free_tab((void **)paths);
// 	}
// 	binary_exec(token, env, path);
// 	ft_free((void **)&path);
// }

// static void	dispatch(void *item, t_list *env)
// {
// 	t_token	*token;

// 	token = (t_token *)item;
// 	if (token->type == TOK_SEMI)
// 	{
// 		// TODO:
// 		printf("SEMI\n");
// 	}
// 	else if (token->type == TOK_PIPE)
// 	{
// 		// TODO:
// 		printf("PIPE\n");
// 	}
// 	else if (token->type == TOK_REDIR)
// 	{
// 		// TODO:
// 		printf("REDIR \n");
// 	}
// 	else if (token->type == TOK_DOLLAR)
// 	{
// 		// TODO:
// 		printf("DOLLAR \n");
// 		token_print(token);
// 	}
// 	else if (token->type == TOK_COMMAND)
// 	{
// 		exec_cmd(token, env);
// 	}
// }

void	exec(t_btree *tree, t_list *env)
{
	// my_btree_prefix(tree, env, &dispatch);
	(void)env;
	btree_apply_prefix(tree, &token_print);

	btree_apply_prefix(tree, &token_destroy);
	btree_free(&tree);
}








/*
	verif si le fichier est executable par nous
		d rwx rwx rwx
		0 000 000 000
		1 111 111 111

		- rwx r-x r-x
		0 111 101 101	<- retour de stat
		0 001 000 000	<- masque
	ET	-------------
		0 000 000 000	<- perm ok
*/
