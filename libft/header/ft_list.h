/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:05:24 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/16 19:01:38 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

t_list			*ft_create_elem(void *data);
void			ft_list_push_back(t_list **begin_list, void *data);
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			my_list_foreach_if(t_list *begin_list, void (*f)(t_list *, void *,
					unsigned int), void *data_ref, int (*cmp)());
#endif
