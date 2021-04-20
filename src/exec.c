/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:18:53 by agautier          #+#    #+#             */
/*   Updated: 2021/04/20 19:32:546 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	my_btree_prefix(t_btree *root, t_list *env, void (*f)(void *, t_list *env))
{
	if (!root)
		return ;
	f(root->item, env);
	my_btree_prefix(root->left, env, f);
	my_btree_prefix(root->right, env, f);
}

static void	exec_cmd(t_token *token, t_list *env)
{
	unsigned int	i;
	int				fd;
	const char		*builtin_names[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	unsigned char	(*builtins[7])(t_token *cmd, int fd, t_list **env) = {
		&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export, &builtin_unset, &builtin_env, &builtin_exit};

	fd = STDOUT_FILENO;	// TODO:
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(token->data[0], (char *)builtin_names[i]))
		{
			builtins[i](token, fd, &env);
			return ;
		}
		i++;
	}
	printf("not a builtin but a binary\n");
	// token->data[0]
	// is not a path		=> ls
		// check if file exist in path
		// find binary in path then jump to 3rd step

	// si path absolute		=> /bin/ls
		// verif si le fichier est executable par nous

	// is path relative 	=> ../ls
		// verif si le fichier existe et est executable par nous

	// creer un sous processus
	// executer le binaire une fois trouve
	// recup la sortie ?
}

static void	dispatch(void *item, t_list *env)
{
	t_token	*token;

	token = (t_token *)item;
	if (token->type == TOK_SEMI)
	{
		// TODO:
		printf("SEMI\n");
	}
	else if (token->type == TOK_PIPE)
	{
		// TODO:
		printf("PIPE\n");
	}
	else if (token->type == TOK_REDIR)
	{
		// TODO:
		printf("REDIR \n");
	}
	else if (token->type == TOK_COMMAND)
	{
		exec_cmd(token, env);
	}
}

void	exec(t_btree *tree, t_list *env)
{
	my_btree_prefix(tree, env, &dispatch);

	btree_apply_prefix(tree, &token_destroy);
	btree_free(&tree);
}
