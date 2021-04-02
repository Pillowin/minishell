/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:06:55 by agautier          #+#    #+#             */
/*   Updated: 2021/03/22 16:114:26 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	TODO: error func
**	TODO: toujours \n de present ? Si non ca segv
*/

/*
**	Accepted syntax :
**		TOK_WORD TOK_SEMI				OR
**		TOK_WORD TOK_SEMI TOK_NEWLINE	OR
**		TOK_WORD TOK_SEMI TOK_WORD	OR
**		TOK_WORD TOK_SEMI TOK_DGREAT	OR
**		TOK_WORD TOK_SEMI TOK_GREAT	OR
**		TOK_WORD TOK_SEMI TOK_LESS
*/

void	check_semi(t_list *tokens, void *data, unsigned int i)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	if (!i)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return ;
	}
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev->type != TOK_WORD)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return ;
	}
	if (next->type == TOK_PIPE || next->type == TOK_SEMI)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_PIPE TOK_WORD	OR
**		TOK_WORD TOK_PIPE TOK_DGREAT	OR
**		TOK_WORD TOK_PIPE TOK_GREAT	OR
**		TOK_WORD TOK_PIPE TOK_LESS
*/

void	check_pipe(t_list *tokens, void *data, unsigned int i)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	if (!i)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return ;
	}
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev->type != TOK_WORD)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return ;
	}
	if (next->type == TOK_PIPE || next->type == TOK_SEMI || next->type == TOK_NEWLINE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_DGREAT TOK_WORD	OR
**		TOK_PIPE TOK_DGREAT TOK_WORD	OR
**		TOK_SEMI TOK_DGREAT TOK_WORD	OR
**		         TOK_DGREAT TOK_WORD
*/

void	check_dgreat(t_list *tokens, void *data, unsigned int i)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT || prev->type == TOK_LESS))
	{
		printf("bash: syntax error near unexpected token `>>'\n");
		return ;
	}
	if (next->type != TOK_WORD)
	{
		printf("bash: syntax error near unexpected token `>>'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_GREAT TOK_WORD	OR
**		TOK_PIPE TOK_GREAT TOK_WORD	OR
**		TOK_SEMI TOK_GREAT TOK_WORD	OR
**		         TOK_GREAT TOK_WORD
*/

void	check_great(t_list *tokens, void *data, unsigned int i)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT || prev->type == TOK_LESS))
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return ;
	}
	if (next->type != TOK_WORD)
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_LESS TOK_WORD	OR
**		TOK_PIPE TOK_LESS TOK_WORD	OR
**		TOK_SEMI TOK_LESS TOK_WORD	OR
**		         TOK_LESS TOK_WORD
*/

void	check_less(t_list *tokens, void *data, unsigned int i)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT || prev->type == TOK_LESS))
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return ;
	}
	if (next->type != TOK_WORD)
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return ;
	}
}
