/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:57:46 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 18:45:43 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

/*
**	check_token.c
*/

int	check_semi(t_list *tokens, unsigned int i, t_err *err);
int	check_pipe(t_list *tokens, unsigned int i, t_err *err);
int	check_dgreat(t_list *tokens, unsigned int i, t_err *err);
int	check_great(t_list *tokens, unsigned int i, t_err *err);
int	check_less(t_list *tokens, unsigned int i, t_err *err);

/*
**	parser.c
*/

int	parser(t_list **tokens, t_err *err);
int	check_tokens(t_list *tokens, t_err *err);

/*
**	tree.c
*/

int	create_tree(t_list *tokens, t_err *err);

/*
**	merge.c
*/

int	redir_merge(t_list **tokens, t_err *err);
int	command_merge(t_list **tokens, t_err *err);
int	dgreat_merge(t_list **tokens, t_err *err);


#endif
