/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:07 by agautier          #+#    #+#             */
/*   Updated: 2021/04/14 18:40:23 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPANSION_H
# define MINISHELL_EXPANSION_H

int		check_pair(t_list **tokens, t_list *curr, t_tok_type type, t_err *err);
t_list	*case_neighbour(t_list **tokens, t_list *prev, t_list *curr);
int		fetch_data(t_list **prev, t_list **curr, char ***str, t_tok_type type);
t_list	*update_list(t_list **tokens, t_list **prev, t_list *curr, t_list *new);

t_list	*expand_quote(t_list **tokens, t_list **prev, t_tok_type t, t_err *err);
t_list	*expand_dquote(t_list **tokens, t_list **prev, t_err *err);
t_list	*expand_bslash(t_list **toks, t_list **prev, t_list *next, t_err *err);
void	expand_dollar(void);

int		expand(t_list **tokens, t_err *err);

#endif
