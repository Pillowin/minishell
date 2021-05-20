/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:51:20 by agautier          #+#    #+#             */
/*   Updated: 2021/05/20 20:10:35 by agautier         ###   ########.fr       */
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
int		gc_strsdup(char ***strs, size_t size, char *str, t_list **gc);
int		my_calloc(size_t count, size_t size, void **ptr, t_list **gc);
size_t	ft_strslen(char **strs);
int		is_var(void *data, void *ref);
char	is_name(char *word, char delimiter);
t_dlist	*gc_create_delem(t_list **gc, void *data);
void	gc_dlist_push_back(t_list **gc, t_dlist **begin_list, void *data);
int		ft_putchar(int c);
t_dlist	*dlst_last(t_dlist *dlist);
void	waitall(void);
// char	tab_init(char **s1, char **s2, char **s3, t_list **gc);
void	var_print(void *data);
void	gc_btree_free(t_btree **root, t_list **gc);
void	gc_btree_apply_prefix(t_btree *root, void (*applyf)(void *, t_list **),
			t_list **gc);
char	*gc_strjoin(char const *s1, char const *s2, t_list **gc);
void	gc_free_tab(void **data, t_list **gc);
void	gc_lstdel(void **list, t_list **gc);
t_list	*gc_lstnew(void *data, t_list **gc);

/*
**	gc_utils.c
*/
void	gc_list_push_back(t_list **begin_list, void *data, t_list **gc);
void	gc_list_clear(t_list *begin_list, t_list **gc);
void	gc_list_remove_var(t_list **begin_list, void *data_ref, t_list **gc);
void	gc_list_rm_tok_if(t_list **begin_list, void *data_ref,
			int (*cmp)(), t_list **gc);
void	gc_list_foreach(t_list *begin_list, void (*f)(void *, t_list **),
			t_list **gc);
void	gc_lstdelone(t_list *lst, void (*del)(void *, t_list **), t_list **gc);
char	*gc_strdup(char *str, t_list **gc);
t_list	*lstdup(t_list *lst, t_list **gc);

/*
** cmp
*/
int	cmp_var_name(void *data, void *ref);

#endif
