/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:32:56 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:44:13 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include "ft_list.h"

typedef struct s_dlist	t_dlist;
typedef struct s_var	t_var;

void	gc_btree_free(t_btree **root, t_list **gc);
void	*gc_calloc(t_list **gc, size_t count, size_t size);
void	gc_clean(t_list **gc);
t_dlist	*gc_create_delem(t_list **gc, void *data);
void	gc_dlist_push_back(t_list **gc, t_dlist **begin_list, void *data);
void	gc_free_tab(void **data, t_list **gc);
void	gc_free(t_list **gc, void **ptr);
void	gc_list_clear(t_list *begin_list, t_list **gc);
void	gc_list_push_back(t_list **begin_list, void *data, t_list **gc);
void	gc_list_remove_var(t_list **begin_list, void *data_ref, t_list **gc);
t_list	*gc_lstnew(void *data, t_list **gc);
void	gc_lstdel(void **list, t_list **gc);
void	gc_lstdelone(t_list *lst, void (*del)(void *, t_list **), t_list **gc);
void	gc_register(t_list **gc, void *ptr);
char	*gc_strdup(char *str, t_list **gc);
char	*gc_strjoin(char const *s1, char const *s2, t_list **gc);
int		gc_strsdup(char ***strs, size_t size, char *str, t_list **gc);
void	gc_unregister(t_list **gc, void *ptr);
void	gc_list_foreach(t_list *begin_list, void (*f)(void *, t_list **),
			t_list **gc);
void	gc_list_rm_tok_if(t_list **begin_list, void *data_ref,
			int (*cmp)(), t_list **gc);
void	gc_btree_apply_prefix(t_btree *root, void (*applyf)(void *, t_list **),
			t_list **gc);

#endif
