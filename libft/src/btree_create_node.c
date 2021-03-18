/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:22:26 by mamaquig          #+#    #+#             */
/*   Updated: 2021/03/04 21:57:03 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/*
**	Alloue un nouvel élément, initialise son item à la valeur du paramètre et
**	tous les autres éléments à 0.
*/

t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	node = (t_btree *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
