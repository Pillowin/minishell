#include "minishell.h"

/*
**	Compare var name.
*/
static int	cmp(void *data, void *ref)
{
	if (!data || !ref || !(((t_var *)data)->name) || !(((t_var *)ref)->name))
		return (FAILURE);
	return (ft_strcmp(((t_var *)data)->name, ((t_var *)ref)->name));
}

/*
**	Print environnement variables with "declare -x".
*/
static void	print_env(void *data)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(((t_var *)data)->name, STDOUT_FILENO);
	if (*((t_var *)data)->equal)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		if (((t_var *)data)->value)
			ft_putstr_fd(((t_var *)data)->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/*
**	export
**	Print ASCII ordered environment.
*/
static char	export_no_arg(t_list **env, t_err *err)
{
	t_list	*env_tmp;

	env_tmp = lstdup(*env, err->gc);
	ft_list_sort(&env_tmp, &cmp);
	ft_list_foreach(env_tmp, &print_env);
	gc_list_clear(env_tmp, err->gc);
	return (SUCCESS);
}

/*
**	If no arg, print environment.
**	Else add variable to environment.
*/
char	builtin_export(t_token *cmd, t_list **env, t_err *err)
{
	unsigned int	i;
	t_var			*var;

	if (!(cmd->data[1]))
		return (export_no_arg(env, err));
	i = 1;
	while (cmd->data[i])
	{
		if (!is_name(cmd->data[i], '='))
		{
			perr_msg(cmd->data[0], cmd->data[1], err->message[EXPORT], err->gc);
			i++;
			continue ;
		}
		var = var_init(cmd->data[i], err->gc);
		if (!var)
			return ((long)error(err, FATAL, NULL, NULL));
		env_update(env, var, err->gc);
		i++;
	}
	return (SUCCESS);
}
