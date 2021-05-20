/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 16:55:09 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENV_H
# define MINISHELL_ENV_H

typedef struct s_var
{
	char	*name;
	char	*equal;
	char	*value;
}	t_var;

/*
**	env.c
*/
void	env_update(t_list **env, t_var *var, t_list **gc);
t_list	*env_init(char **envp, t_list **gc);
char	**env_to_tab(t_list *env, t_list **gc);

/*
**	var.c
*/
t_var	*var_init(char *str, t_list **gc);
void	var_destroy(void *data, t_list **gc);
char	*var_get_name(char *var, t_list **gc);
char	*var_get_equal(char *var, t_list **gc);
char	*var_get_value(char *var, t_list **gc);

#endif
