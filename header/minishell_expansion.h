/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 20:30:20 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPANSION_H
# define MINISHELL_EXPANSION_H

t_list	*expand_quote(t_list **tokens, t_list **prev, t_tok_type t, t_err *err);
t_list	*expand_dquote(t_list **tokens, t_list **prev, t_list *env, t_err *err);
t_list	*expand_bslash(t_list **toks, t_list **prev, t_list *next, t_err *err);
t_list	*expand_dollar(t_list **toks, t_list **prev, t_list *env, t_err *err);

char	expand(t_list **done, t_list **tokens, t_list *env, t_err *err);
char	*fetch_name(char **word, t_err *err);
t_list	*fetch_value(t_list *next, char *name, t_list *env, t_err *err);

#endif
