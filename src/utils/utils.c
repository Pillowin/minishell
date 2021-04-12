/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:59:09 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 18:39:556 by agautier         ###   ########.fr       */
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

/*
**	Return 0 if type == data->type
*/

int	is_tok_type(t_token *data, void *type)
{
	if (data->type == (t_tok_type)type)
		return (0);
	return (1);
}

/*
**	
*/

int	ft_strsdup(char ***strs, size_t size, char *str)
{
	*strs = (char **)ft_calloc(size + 1, sizeof(**strs));
	if (!(*strs))
		return (FAILURE);
	*strs[0] = ft_strdup(str);
	if (!(*strs[0]))
	{
		ft_free((void **)&(*strs));
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
**
*/

int	my_calloc(size_t count, size_t size, void **ptr)
{
	size_t	i;

	count++;
	*ptr = malloc(count * size);
	if (!*ptr)
		return (FAILURE);
	i = 0;
	while (i < size * count)
	{
		((unsigned char *)(*ptr))[i] = '\0';
		i++;
	}
	return (SUCCESS);
}
