/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:00:19 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/26 18:49:59 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Applique la fonction passée en paramètre à l’item de chaque node,
**	en parcourant l’arbre de manière prefix.
**
**	Dans le parcours préfixe, la racine est traitée avant les appels récursifs
**	sur les sous-arbres gauche et droit (faits dans cet ordre).
**
**			┌-----1-----┐
**		┌---2---┐	┌---5---┐
**		3		4	6		7
*/
void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	applyf(root->item);
	btree_apply_prefix(root->left, applyf);
	btree_apply_prefix(root->right, applyf);
}
