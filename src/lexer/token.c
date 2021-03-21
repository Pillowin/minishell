/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:48:29 by agautier          #+#    #+#             */
/*   Updated: 2021/03/21 20:18:13 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Alloc, init and return a new t_token.
*/

t_token	*token_init(int type, char **data)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->data = data;
	return (token);
}

/*
**	Return string corresponding to token type.
**
**	TODO: make prettier
*/

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
	if (type == TOKEN_REDIR)
		return ("TOKEN_REDIR");
	if (type == TOKEN_COMMAND)
		return ("TOKEN_COMMAND");
	return ("TOKEN_UNKNOW");
}

/*
**	Print t_token infos.
**
**	TODO: if !token err func instead of printf
*/

void	token_print(void *token)
{
	t_token	*tok;
	int		i;

	if (!token)
	{
		printf("token = NULL\n");
		return ;
	}
	tok = (t_token *)token;
	printf("token = %s\t", token_type_to_str(tok->type));
	i = 0;
	while ((tok->data)[i])
	{
		printf("%s ", (tok->data)[i]);
		i++;
	}
	printf("\n");
}
