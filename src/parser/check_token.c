/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:06:55 by agautier          #+#    #+#             */
/*   Updated: 2021/03/16 20:06:02 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	printf("check_semi\n");
	printf("i = %u\n", i);
	if (!i)	// TODO: check if list_at(i+1) segv or no need because \n ?
	{
		printf("bash: syntax error near unexpected token `;'\n");	// TODO: err func
		return ;
	}
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	printf("prev : ");
	token_print(prev);
	printf("curr : ");
	token_print(curr);
	printf("next : ");
	token_print(next);
	
	if (prev->e_type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `;'\n");	// TODO: err func
		return ;
	}
	if (next->e_type == TOKEN_PIPE || next->e_type == TOKEN_SEMI)
	{
		printf("bash: syntax error near unexpected token `;'\n");	// TODO: err func
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

	printf("check_pipe\n");
	printf("i = %u\n", i);
	if (!i)	// TODO: check if list_at(i+1) segv or no need because \n ?
	{
		printf("bash: syntax error near unexpected token `|'\n");	// TODO: err func
		return ;
	}
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	curr = (t_token *)data;
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	printf("prev : ");
	token_print(prev);
	printf("curr : ");
	token_print(curr);
	printf("next : ");
	token_print(next);
	
	if (prev->e_type != TOKEN_WORD)
	{
		printf("bash: syntax error near unexpected token `|'\n");	// TODO: err func
		return ;
	}
	if (next->e_type == TOKEN_PIPE || next->e_type == TOKEN_SEMI || next->e_type == TOKEN_NEWLINE)
	{
		printf("bash: syntax error near unexpected token `|'\n");	// TODO: err func
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
	(void)tokens;
	(void)data;
	(void)i;
	//TODO: vérifier les erreurs possible
	printf("check_dgreat\n");
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
	(void)tokens;
	(void)data;
	(void)i;
	//TODO: vérifier les erreurs possible
	printf("check_great\n");
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
	(void)tokens;
	(void)data;
	(void)i;
	//TODO: vérifier les erreurs possible
	printf("check_less\n");
}
