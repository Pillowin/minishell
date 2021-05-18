/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:53:09 by agautier          #+#    #+#             */
/*   Updated: 2021/05/10 17:06:002 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	print var
*/
void	print_var(void *data)	// TODO: remove ?
{
	t_var	*var;

	var = (t_var *)data;
	ft_putstr_fd(var->name, STDOUT_FILENO);
	ft_putstr_fd(var->equal, STDOUT_FILENO);
	ft_putstr_fd(var->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/*
**
*/

char	is_builtin(t_token *token, t_fd *fd, t_list **env, t_err *err)
{
	unsigned int	i;
	const char		*builtin_names[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	unsigned char	(* const builtins[7])(t_token *cmd, t_list **env, t_err *err) = {
		&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export, &builtin_unset, &builtin_env, &builtin_exit};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(token->data[0], (char *)builtin_names[i]))
		{
			if (!builtins[i](token, env, err))	// TODO: set error in each builtin
			{
				if (fd->is_child)
				{
					gc_clean(err->gc);
					exit(g_exit_status & 0x00FF);
				}
				return (FAILURE);
			}
			if (fd->is_child)
			{
				if (close(fd->pipes[OUT]) == -1) //OUT redevenir STD_OUT
					return ((long)error(err, FATAL, NULL, NULL));
				fd->pipes[OUT] = STDOUT_FILENO;
				gc_clean(err->gc);
				exit(g_exit_status & 0x00FF);
			}
			return (DONE);
		}
		i++;
	}
	return (SUCCESS);
}
