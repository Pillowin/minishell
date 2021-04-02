/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/02 16:15:02 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPANSION_H
# define MINISHELL_EXPANSION_H

/*
**	expand.c
*/

void	expand(t_list **tokens);

/*
**	expand_quote.c
*/

t_list	*expand_quote(t_list **prev, t_list *next);

/*
**	expand_dquote.c
*/

t_list	*expand_dquote(t_list **prev, t_list *next);

/*
**	expand_bslash.c
*/

t_list	*expand_bslash(t_list **prev, t_list *next);

/*
**	expand_dollar.c
*/

void	expand_dollar(void);

// char	*expand_quote(t_lexer *lexer);
// char	*get_char_in_quote(t_lexer *lexer);

/*
**	
*/

#endif
