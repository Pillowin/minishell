/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_btree_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:41:36 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:12 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free les elements de l'arbre
*/
void	gc_btree_free(t_btree **root, t_list **gc)
{
	if (!(*root))
		return ;
	gc_btree_free(&((*root)->left), gc);
	gc_btree_free(&((*root)->right), gc);
	gc_free(gc, (void **)&(*root));
}
