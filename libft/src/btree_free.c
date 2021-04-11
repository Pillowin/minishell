/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:29:32 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/08 20:58:224 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Parcours un arbre de maniere suffix afin de free tous ses nodes.
*/

void	btree_free(t_btree **root)
{
	if (!(*root))
		return ;
	btree_free(&((*root)->left));
	btree_free(&((*root)->right));
	ft_free((void **)&(*root));
}
