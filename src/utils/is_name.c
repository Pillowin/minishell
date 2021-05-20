/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:50:23 by mamaquig          #+#    #+#             */
/*   Updated: 2021/05/20 18:52:38 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check si WORD respecte la syntax d'une variable dans ENV.
*/
char	is_name(char *word, char delimiter)
{
	unsigned int	i;

	if (!word)
		return (FAILURE);
	i = 0;
	if (!ft_isalpha(word[i]) && word[i] != '_')
		return (FAILURE);
	i++;
	while (word[i] && word[i] != delimiter)
	{
		if (!ft_isalnum(word[i]) && word[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
