/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:59:09 by agautier          #+#    #+#             */
/*   Updated: 2021/03/25 18:39:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	 Return 1 if c is a space or a \n else return 0
*/

int	ft_is_end_word(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

/*
**	Return 1 if c is a token else return 0
*/

int	ft_is_token(char c)
{
	if (c == ' '
		|| c == '\n'
		|| c == '\\'
		|| c == '\''
		|| c == '"'
		|| c == '$'
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == ';')
		return (1);
	return (0);
}
