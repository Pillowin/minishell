/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:47:53 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:41 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoi 0 si le type de data correspond au type passé en paramètre.
*/
int	is_tok_type(t_token *data, void *type)
{
	if (data->type == (long)type)
		return (0);
	return (1);
}
