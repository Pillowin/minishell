/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:53:01 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 19:20:58 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Attend que tout les sous-processus meurts.
*/
void	waitall(void)
{
	int	ret;

	while (1)
	{
		ret = waitpid(-1, NULL, 0);
		if (ret == -1)
			break ;
	}
}
