/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_tok_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:39:51 by agautier          #+#    #+#             */
/*   Updated: 2021/05/26 16:40:09 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Comparer l'enum avec les éléments (token) du tableau.
*/
int	cmp_token_type(t_token *lstdata, int *data)
{
	if ((int)(lstdata->type) == *data)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
