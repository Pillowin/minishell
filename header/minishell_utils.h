/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:54:07 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

/*
**	utils.c
*/
int		ft_is_end_word(char c);
int		ft_is_token(char c);
int		is_tok_type(t_token *data, void *type);
int		my_calloc(size_t count, size_t size, void **ptr, t_list **gc);
size_t	ft_strslen(char **strs);
int		is_var(void *data, void *ref);
char	is_name(char *word, char delimiter);
t_dlist	*dlst_last(t_dlist *dlist);
void	waitall(void);
void	var_print(void *data);
t_list	*lstdup(t_list *lst, t_list **gc);
int		ft_putchar(int c);

/*
** cmp
*/
int		cmp_token_type(t_token *lstdata, int *data);
int		cmp_var_name(void *data, void *ref);

#endif
