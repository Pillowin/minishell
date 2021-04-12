/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 18:48:14 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPANSION_H
# define MINISHELL_EXPANSION_H

/*
**	expand.c
*/

int	expand(t_list **tokens, t_err *err);

/*
**	expand_quote.c
*/

t_list	*expand_quote(t_list **tokens, t_list **prev, t_list *next, t_err *err);

/*
**	expand_dquote.c
*/

t_list	*expand_dquote(t_list **tokens, t_list **prev, t_err *err);

/*
**	expand_bslash.c
*/

t_list	*expand_bslash(t_list **tokens, t_list **prev, t_list *next, t_err *err);

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
