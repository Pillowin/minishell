/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:48:29 by agautier          #+#    #+#             */
/*   Updated: 2021/03/15 17:05:42 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_init(int type, char *data)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->data = data;
	token->e_type = type;
	return (token);
}

char	*token_type_to_str(int type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (type == TOKEN_LESS)
		return ("TOKEN_LESS");
	if (type == TOKEN_GREAT)
		return ("TOKEN_GREAT");
	if (type == TOKEN_DGREAT)
		return ("TOKEN_DGREAT");
	if (type == TOKEN_SEMI)
		return ("TOKEN_SEMI");
	if (type == TOKEN_NEWLINE)
		return ("TOKEN_NEWLINE");
	return ("TOKEN_UNKNOW");
}

void	token_print(void *token)
{
	t_token	*tok;

	tok = (t_token *)token;
	printf("token = %s\t", token_type_to_str(tok->e_type));
	printf("%s\n", tok->data);
}
