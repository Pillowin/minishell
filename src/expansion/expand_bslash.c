/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmamaqquig <mmamaqquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:46 by agautier          #+#    #+#             */
/*   Updated: 2021/03/30 22:14:53 by mmamaqquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Fct appelé lorsque lexer->c = \
**	TODO: handle \newline
*/

/*
**	without ""
**	Preserves the literal value of the next character that follows, with the exception of newline.
**
**	whith ""
**	if next char is not $ or " or \ or NEWLINE print \
**	Preserves the literal value of the next character that follows, with the exception of newline.
*/

/*
**	token = TOK_WORD        echo  
**	token = TOK_SPACE             
**	token = TOK_WORD        je    
**	token = TOK_SPACE             <-- previous de expand.c, passé en paramètre à expand_quote
**	token = TOK_BSLASH      \     <-- curr de expand.c previous de expand.c, passé en paramètre à expand_quote
**	token = TOK_SPACE             <-- next de expand.c, passé en paramètre à expand_quote
**	token = TOK_WORD        suis  
**	token = TOK_SPACE             
**	token = TOK_WORD        an    
**	token = TOK_BSLASH      \     
**	token = TOK_DQUOTE      "     
**	token = TOK_WORD        toine 
**	token = TOK_NEWLINE           
*/

/*
**	without ""
**	Preserves the literal value of the next character that follows, with the exception of newline.
*/

t_list	*expand_bslash(t_list **prev, t_list *next)
{
	t_list		*new;
	t_token		*token;
	char		**str;

	if (((t_token *)(next->data))->type == TOK_WORD || ((t_token *)(next->data))->type == TOK_NEWLINE)
	{
		// TODO: free curr
		(*prev)->next = next;
		return ((*prev)->next);
	}
	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
		return (NULL);
	*str = (char *)ft_calloc(1 + 1, sizeof(**str));
	if (!*str)
		return (NULL);
	**str = **(((t_token *)(next->data))->data);
	token = token_init(TOK_WORD, str);
	new = ft_lstnew(token);
	new->next = next->next;
	(*prev)->next = new;
	return (new);
}
