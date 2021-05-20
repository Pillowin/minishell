/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 15:41:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# define FAILURE		0
# define SUCCESS		1
# define DONE			2

typedef enum e_err_code
{
	NONE = 0,
	FATAL,
	MULTILINE_QUOTE,
	MULTILINE_DQUOTE,
	MULTILINE_BSLASH,
	SYNTAX_SEMI,
	SYNTAX_PIPE,
	SYNTAX_DGREAT,
	SYNTAX_GREAT,
	SYNTAX_LESS,
	HOME_NOT_SET,
	OLDPWD_NOT_SET,
	TOO_MANY_ARG,
	NOT_FOUND,
	NO_SUCH_FILE,
	IS_A_DIR,
	PERM,
	EXPORT,
	ERR_NO
}	t_err_code;

typedef struct s_err
{
	t_list			**gc;
	char			**message;
	unsigned char	code;
	char			*cmd_name;
}	t_err;

/*
**	error.c
*/
void	err_init(char **err_msg);
void	perr_msg(char *cmd_name, char *arg, char *msg, t_list **gc);
void	*error(t_err *err, t_err_code code, void **ptr,
			void (*free_fct)(void **, t_list **));

#endif
