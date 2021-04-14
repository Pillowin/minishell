/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:06:55 by agautier          #+#    #+#             */
/*   Updated: 2021/04/14 21:4300 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Accepted syntax :
**		TOK_WORD TOK_SEMI				OR
**		TOK_WORD TOK_SEMI TOK_NEWLINE	OR
**		TOK_WORD TOK_SEMI TOK_WORD		OR
**		TOK_WORD TOK_SEMI TOK_DGREAT	OR
**		TOK_WORD TOK_SEMI TOK_GREAT		OR
**		TOK_WORD TOK_SEMI TOK_LESS
*/

int	check_semi(t_list *tokens, unsigned int i, t_err *err)
{
	t_token	*prev;
	t_token	*next;

	if (!i)
		return ((long)error(err, SYNTAX_SEMI, (void **)tokens, &ft_lstdel));
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev->type != TOK_WORD || next->type == TOK_PIPE
		|| next->type == TOK_SEMI)
		return ((long)error(err, SYNTAX_SEMI, (void **)&tokens, &ft_lstdel));
	return (SUCCESS);
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_PIPE TOK_WORD		OR
**		TOK_WORD TOK_PIPE TOK_DGREAT	OR
**		TOK_WORD TOK_PIPE TOK_GREAT		OR
**		TOK_WORD TOK_PIPE TOK_LESS
*/

int	check_pipe(t_list *tokens, unsigned int i, t_err *err)
{
	t_token	*prev;
	t_token	*next;

	if (!i)
		return ((long)error(err, SYNTAX_PIPE, (void **)tokens, &ft_lstdel));
	prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if (prev->type != TOK_WORD || next->type == TOK_PIPE
		|| next->type == TOK_SEMI || next->type == TOK_NEWLINE)
		return ((long)error(err, SYNTAX_PIPE, (void **)&tokens, &ft_lstdel));
	return (SUCCESS);
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_DGREAT TOK_WORD	OR
**		TOK_PIPE TOK_DGREAT TOK_WORD	OR
**		TOK_SEMI TOK_DGREAT TOK_WORD	OR
**		         TOK_DGREAT TOK_WORD
*/

int	check_dgreat(t_list *tokens, unsigned int i, t_err *err)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if ((prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT
				|| prev->type == TOK_LESS)) || next->type != TOK_WORD)
		return ((long)error(err, SYNTAX_DGREAT, (void **)&tokens, &ft_lstdel));
	return (SUCCESS);
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_GREAT TOK_WORD	OR
**		TOK_PIPE TOK_GREAT TOK_WORD	OR
**		TOK_SEMI TOK_GREAT TOK_WORD	OR
**		         TOK_GREAT TOK_WORD
*/

int	check_great(t_list *tokens, unsigned int i, t_err *err)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if ((prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT
				|| prev->type == TOK_LESS)) || next->type != TOK_WORD)
		return ((long)error(err, SYNTAX_GREAT, (void **)&tokens, &ft_lstdel));
	return (SUCCESS);
}

/*
**	Accepted syntax :
**		TOK_WORD TOK_LESS TOK_WORD	OR
**		TOK_PIPE TOK_LESS TOK_WORD	OR
**		TOK_SEMI TOK_LESS TOK_WORD	OR
**		         TOK_LESS TOK_WORD
*/

int	check_less(t_list *tokens, unsigned int i, t_err *err)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	if (i)
		prev = (t_token *)(ft_list_at(tokens, i - 1)->data);
	next = (t_token *)(ft_list_at(tokens, i + 1)->data);
	if ((prev && (prev->type == TOK_GREAT || prev->type == TOK_DGREAT
				|| prev->type == TOK_LESS)) || next->type != TOK_WORD)
		return ((long)error(err, SYNTAX_LESS, (void **)&tokens, &ft_lstdel));
	return (SUCCESS);
}
