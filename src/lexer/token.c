/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:04:51 by agautier          #+#    #+#             */
/*   Updated: 2021/04/13 16:40:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_token.
*/

int	token_init(t_tok_type type, char **data, t_token **token)
{
	if (!my_calloc(1, sizeof(**token), (void **)token))
		return (FAILURE);
	(*token)->type = type;
	(*token)->data = data;
	return (SUCCESS);
}

/*
**	Destroy and free a t_token.
*/

void	token_destroy(void *ptr)
{
	t_token			*token;
	unsigned int	i;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	i = 0;
	while (token->data[i])
	{
		ft_free((void **)&(token->data[i]));
		i++;
	}
	ft_free((void **)&(token->data));
	ft_free((void **)&token);
}
