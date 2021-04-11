/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:57:46 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 15:23:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

/*
**	check_token.c
*/

void	check_semi(t_list *tokens, unsigned int i);
void	check_pipe(t_list *tokens, unsigned int i);
void	check_dgreat(t_list *tokens, unsigned int i);
void	check_great(t_list *tokens, unsigned int i);
void	check_less(t_list *tokens, unsigned int i);

/*
**	parser.c
*/

void			check_tokens(t_list *tokens);
void			parse_tokens(t_list **tokens);

/*
**	tree.c
*/

void	create_tree(t_list *tokens);

/*
**	merge.c
*/

void	redir_merge(t_list **tokens);
void	command_merge(t_list **tokens);
void	dgreat_merge(t_list **tokens);


#endif
