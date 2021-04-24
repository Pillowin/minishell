/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:48:27 by agautier          #+#    #+#             */
/*   Updated: 2021/03/31 16:22:29by aggreteer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	print var
*/
void	print_var(void *data)
{
	t_var	*var;

	var = (t_var *)data;
	printf("%s%s%s\n", var->name, var->equal, var->value);
}

int	main(int argc, char **argv, char **envp)
{
	unsigned int	i;
	t_list			*env;
	t_err			err;
	char 			*err_msg[10];	// TODO:
	char			buf[4096];		// TODO:

	(void)argc;
	(void)argv;

	err_init(err_msg);
	err = (t_err){err_msg, 0};

	env = env_init(envp);
	if (!env)
	{
		ft_list_foreach(env, &var_destroy);
		ft_list_clear(env, &ft_free);
		return (EXIT_FAILURE);	// TODO: use error
	}

	while (1)
	{
		i = 0;
		while (i < 4096)
		{
			buf[i] = '\0';
			i++;
		}
		if (!prompt(&env))
		{
			ft_list_foreach(env, &var_destroy);
			ft_list_clear(env, &ft_free);
			return (EXIT_FAILURE);	// TODO: use error
		}
		if (read(STDIN_FILENO, buf, 4096) > 0)
		{
			if(!(lexer(buf, &err, env)))
			{
				printf("erreur dans minishell\n");
				// return (EXIT_FAILURE);
				continue ;
			}
		}
		else
		{
			printf(" tu c pa fer d pro gramme idiot bete de moche. pday va\n");
			return (EXIT_FAILURE);
		}
	}


	ft_list_foreach(env, &var_destroy);
	ft_list_clear(env, &ft_free);
	return (EXIT_SUCCESS);
}





// void	test_echo(int argc, char **argv)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_echo(&cmd, STDOUT_FILENO);
// 	}
// 	else
// 		printf("Usage : ./minishell echo -n toto tata.\n");
// }

// void	test_cd(int argc, char **argv, t_list **env)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_cd(&cmd, env);
// 	}
// 	else
// 		printf("Usage : ./minishell cd path.\n");
// }

// void	test_pwd(int argc, char **argv)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_pwd(&cmd, STDOUT_FILENO);
// 	}
// 	else
// 		printf("Usage : ./minishell pwd.\n");
// }

// void	test_env(int argc, char **argv, t_list *env)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_env(&cmd, STDOUT_FILENO, env);
// 	}
// 	else
// 		printf("Usage : ./minishell env.\n");
// }

// void	test_export(int argc, char **argv, t_list *env)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_export(&cmd, STDOUT_FILENO, env);
// 	}
// 	else
// 		printf("Usage : ./minishell export var_name=value.\n");
// }

// void	test_unset(int argc, char **argv, t_list **env)
// {
// 	t_token cmd;

// 	if (argc > 1)
// 	{
// 		cmd = (t_token){TOK_COMMAND, &argv[1]};
// 		builtin_unset(&cmd, env);
// 	}
// 	else
// 		printf("Usage : ./minishell unset var.\n");
// }


/*
// ** Fetch name and value
// */
// char	get_var_name_value(char *var, char **name, char **equal, char **value)
// {
// 	unsigned int	i;

// 	*value = ft_strchr(var, '=');
// 	if (*value)
// 	{
// 		i = *value - var + 1;
// 		*value = ft_substr(var, i, ft_strlen(var) - i);
// 		if (!*value)
// 			return (FAILURE);
// 		*equal = ft_strdup("=");
// 		if (!*equal)
// 		{
// 			ft_free((void **)*value);
// 			return (FAILURE);
// 		}
// 		*name = ft_substr(var, 0, i - 1);
// 		if (!*name)
// 		{
// 			ft_free((void **)*equal);
// 			ft_free((void **)*value);
// 			return (FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		*name = ft_strdup(var);
// 		if (!*name)
// 			return (FAILURE);
// 	}
// 	return (SUCCESS);
// }
