/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_btree_apply_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:43:06 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 19:02:13 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Applique la fonction passée en paramètre à l’item de chaque node,
**	en parcourant l’arbre de manière prefix.
*/
void	gc_btree_apply_prefix(t_btree *root, void (*applyf)(void *, t_list **),
								t_list **gc)
{
	if (!root)
		return ;
	applyf(root->item, gc);
	gc_btree_apply_prefix(root->left, applyf, gc);
	gc_btree_apply_prefix(root->right, applyf, gc);
}
