/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:05:24 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/08 1902:941by aagtetrer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H


typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

t_list			*ft_create_elem(void *data);
void			ft_list_push_back(t_list **begin_list, void *data);
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			my_list_foreach_if(t_list *begin_list, int (*f)(t_list *,
					unsigned int), void *data_ref, int (*cmp)());
void			ft_list_clear(t_list *begin_list, void (*free_fct)(void **));
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_list_remove_if(t_list **begin_list, void *data_ref,
							int (*cmp)(), void (*free_fct)(void *));
t_list			*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
t_list			*ft_list_push_strs(size_t size, char **strs);
void			ft_list_sort(t_list **begin_list, int (*cmp)());
int				ft_list_size(t_list *begin_list);

#endif
