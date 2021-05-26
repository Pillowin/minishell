/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:16:02 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 19:16:03 by agautier         ###   ########.fr       */
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
