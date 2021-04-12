/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:04:09 by agautier          #+#    #+#             */
/*   Updated: 2021/04/12 22:42:08 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return string corresponding to token type.
**
**	TODO: make prettier
*/

char	*token_type_to_str(int type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD");
	if (type == TOK_PIPE)
		return ("TOK_PIPE");
	if (type == TOK_LESS)
		return ("TOK_LESS");
	if (type == TOK_GREAT)
		return ("TOK_GREAT");
	if (type == TOK_DGREAT)
		return ("TOK_DGREAT");
	if (type == TOK_SEMI)
		return ("TOK_SEMI");
	if (type == TOK_DQUOTE)
		return ("TOK_DQUOTE");
	if (type == TOK_QUOTE)
		return ("TOK_QUOTE");
	if (type == TOK_NEWLINE)
		return ("TOK_NEWLINE");
	if (type == TOK_REDIR)
		return ("TOK_REDIR");
	if (type == TOK_BSLASH)
		return ("TOK_BSLASH");
	if (type == TOK_SPACE)
		return ("TOK_SPACE");
	if (type == TOK_DOLLAR)
		return ("TOK_DOLLAR");
	if (type == TOK_COMMAND)
		return ("TOK_COMMAND");
	return ("TOK_UNKNOW");
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
	if (!tok->type)
	{
		// printf("\t%p\n", tok);
		printf("\n");
		return ;
	}
	i = 0;
	while ((tok->data)[i])
	{
		if (!(tok->data)[i])
		{
			// printf("\t%p\n", tok);
			printf("\n");
			return ;
		}
		printf("`%s`    ", (tok->data)[i]);
		i++;
	}
	// printf("\t%p\n", tok);
	printf("\n");
}
