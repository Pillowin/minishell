/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:57:46 by agautier          #+#    #+#             */
/*   Updated: 2021/05/18 14:11:33 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

typedef struct s_child
{
	t_list		*left;
	t_list		*right;
	t_list		**gc;
}	t_child;

/*
**	check_token.c
*/
char	check_semi(t_list *tokens, unsigned int i, t_err *err);
char	check_pipe(t_list *tokens, unsigned int i, t_err *err);
char	check_dgreat(t_list *tokens, unsigned int i, t_err *err);
char	check_great(t_list *tokens, unsigned int i, t_err *err);
char	check_less(t_list *tokens, unsigned int i, t_err *err);

/*
**	parser.c
*/
char	check_tokens(t_list *tokens, t_err *err);
char	parser(t_list **tokens, t_err *err, t_list **env);

/*
**	tree.c
*/
char	eat_list(t_list *list, t_btree **node, t_list **gc);
char	create_tree(t_list *tokens, t_list **env, t_err *err);

/*
**	merge.c
*/
char	redir_merge(t_list **tokens, t_err *err);
char	command_merge(t_list **tokens, t_err *err);
char	dgreat_merge(t_list **tokens, t_err *err);

#endif
