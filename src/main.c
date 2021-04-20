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

void	init_msg(char **err_msg)
{
	err_msg[NONE] = "No error\n";
	err_msg[MALLOC] = "Memory allocation failed.\n";
	err_msg[MULTILINE_QUOTE] = "Undefined case : multiline quote command.\n";
	err_msg[MULTILINE_DQUOTE] = "Undefined case : multiline double quote command.\n";
	err_msg[MULTILINE_BSLASH] = "Undefined case : multiline back slash command.\n";
	err_msg[SYNTAX_SEMI] = "bash: syntax error near unexpected token `;'\n";
	err_msg[SYNTAX_PIPE] = "bash: syntax error near unexpected token `|'\n";
	err_msg[SYNTAX_DGREAT] = "bash: syntax error near unexpected token `>>'\n";
	err_msg[SYNTAX_GREAT] = "bash: syntax error near unexpected token `>'\n";
	err_msg[SYNTAX_LESS] = "bash: syntax error near unexpected token `<'\n";
}

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **))
{
	if (free_fct && ptr)
		free_fct(ptr);
	ft_putstr_fd(err->message[code], STDERR_FILENO);
	// set exit_status
		// TODO:
	return(NULL);
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
**	print var
*/
void	print_var(void *data)
{
	t_var	*var;

	var = (t_var *)data;
	printf("%s%s%s\n", var->name, var->equal, var->value);
}

/*
**	
*/
static t_list	*env_init(char **envp)
{
	unsigned int	i;
	t_list			*env;
	t_var			*var;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = var_init(get_name(envp[i]), get_equal(envp[i]), get_value(envp[i]));
		if (!var)
			return (NULL);
		ft_list_push_back(&env, var);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_list *env;
	unsigned int	i;
	char			buf[4096];		// TODO:
	t_err			err;
	char 			*err_msg[10];	// TODO:

	(void)argc;
	(void)argv;

	init_msg(err_msg);
	err = (t_err){err_msg, 0};

	env = env_init(envp);
	if (!env)
	{
		ft_list_foreach(env, &var_destroy);
		ft_list_clear(env, &ft_free);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		i = 0;
		while (i < 4096)
		{
			buf[i] = '\0';
			i++;
		}
		ft_putstr("prompt>");
		if (read(STDIN_FILENO, buf, 4096) > 0)
		{
			if(!(lexer(buf, &err, env)))
			{
				printf("lexer casse2\n");
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






/*
// ** Fetch name and value
// */
// char	get_name_value(char *var, char **name, char **equal, char **value)
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
