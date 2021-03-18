/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:29:32 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/06 22:21:33 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/*
**	Parcours un arbre de maniere suffix afin de free tous ses nodes.
*/

void	btree_free(t_btree **root)
{
	if (!(*root))
		return ;
	btree_free(&((*root)->left));
	btree_free(&((*root)->right));
	free(*root);
	*root = NULL;
}
