/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:06:55 by agautier          #+#    #+#             */
/*   Updated: 2021/03/21 19:41:53 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	TODO: error func
**	TODO: toujours \n de present ? Si non ca segv
*/

/*
**	Accepted syntax :
**		TOKEN_WORD TOKEN_SEMI				OR
**		TOKEN_WORD TOKEN_SEMI TOKEN_NEWLINE	OR
**		TOKEN_WORD TOKEN_SEMI TOKEN_WORD	OR
**		TOKEN_WORD TOKEN_SEMI TOKEN_DGREAT	OR
**		TOKEN_WORD TOKEN_SEMI TOKEN_GREAT	OR
**		TOKEN_WORD TOKEN_SEMI TOKEN_LESS
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
	if (prev->type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return ;
	}
	if (next->type == TOKEN_PIPE || next->type == TOKEN_SEMI)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOKEN_WORD TOKEN_PIPE TOKEN_WORD	OR
**		TOKEN_WORD TOKEN_PIPE TOKEN_DGREAT	OR
**		TOKEN_WORD TOKEN_PIPE TOKEN_GREAT	OR
**		TOKEN_WORD TOKEN_PIPE TOKEN_LESS
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
	if (prev->type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return ;
	}
	if (next->type == TOKEN_PIPE || next->type == TOKEN_SEMI || next->type == TOKEN_NEWLINE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOKEN_WORD TOKEN_DGREAT TOKEN_WORD	OR
**		TOKEN_PIPE TOKEN_DGREAT TOKEN_WORD	OR
**		TOKEN_SEMI TOKEN_DGREAT TOKEN_WORD	OR
**		           TOKEN_DGREAT TOKEN_WORD
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
	if (prev && (prev->type == TOKEN_GREAT || prev->type == TOKEN_DGREAT || prev->type == TOKEN_LESS))
	{
		printf("bash: syntax error near unexpected token `>>'\n");
		return ;
	}
	if (next->type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `>>'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOKEN_WORD TOKEN_GREAT TOKEN_WORD	OR
**		TOKEN_PIPE TOKEN_GREAT TOKEN_WORD	OR
**		TOKEN_SEMI TOKEN_GREAT TOKEN_WORD	OR
**		           TOKEN_GREAT TOKEN_WORD
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
	if (prev && (prev->type == TOKEN_GREAT || prev->type == TOKEN_DGREAT || prev->type == TOKEN_LESS))
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return ;
	}
	if (next->type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return ;
	}
}

/*
**	Accepted syntax :
**		TOKEN_WORD TOKEN_LESS TOKEN_WORD	OR
**		TOKEN_PIPE TOKEN_LESS TOKEN_WORD	OR
**		TOKEN_SEMI TOKEN_LESS TOKEN_WORD	OR
**		           TOKEN_LESS TOKEN_WORD
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
	if (prev && (prev->type == TOKEN_GREAT || prev->type == TOKEN_DGREAT || prev->type == TOKEN_LESS))
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return ;
	}
	if (next->type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return ;
	}
}
