/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:45:33 by agautier          #+#    #+#             */
/*   Updated: 2021/04/18 21:41:552 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(void **data)
{
	unsigned int	i;

	i = 0;
	while ((char **)(data)[i])
	{
		ft_free((void **)&(data[i]));
		i++;
	}
	ft_free((void **)&data);
}

void	ft_lstdel(void **list)
{
	ft_list_foreach(*(t_list **)list, &token_destroy);
	ft_list_clear(*(t_list **)list, &ft_free);
}
