/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:32:56 by agautier          #+#    #+#             */
/*   Updated: 2021/05/17 14:23:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include "ft_list.h"

void	*gc_calloc(t_list **gc, size_t count, size_t size);
void	gc_register(t_list **gc, void *ptr);
void	gc_unregister(t_list **gc, void *ptr);
void	gc_free(t_list **gc, void **ptr);
void	gc_clean(t_list **gc);

#endif
