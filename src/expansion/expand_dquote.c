/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:22:25 by agautier          #+#    #+#             */
/*   Updated: 2021/03/30 23:4:39 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	token = TOK_WORD        echo  
**	token = TOK_SPACE             <-- previous de expand.c, passé en paramètre à expand_quote
**	token = TOK_DQUOTE      "     <-- curr de expand.c previous de expand.c, passé en paramètre à expand_quote
**	token = TOK_WORD        je    <-- next de expand.c, passé en paramètre à expand_quote
**	token = TOK_SPACE             
**	token = TOK_BSLASH      \     
**	token = TOK_SPACE             
**	token = TOK_WORD        suis  
**	token = TOK_SPACE             
**	token = TOK_WORD        an    
**	token = TOK_BSLASH      \     
**	token = TOK_DQUOTE      "     
**	token = TOK_WORD        toine 
**	token = TOK_DQUOTE      "     
**	token = TOK_NEWLINE           
**
**	token = TOK_WORD        echo  
**	token = TOK_SPACE             <-- previous
**	token = TOK_DQUOTE      "     <-- 
**	token = TOK_WORD        je    <-- next
**	token = TOK_SPACE             
**	token = TOK_WORD        \     -> transformation
**	token = TOK_WORD              -> transformation par la fonction expand_bslash
**	token = TOK_WORD        suis  
**	token = TOK_SPACE             
**	token = TOK_WORD        an    
**	token = TOK_WORD        "     -> transformation par la fonction expand_bslash
**	token = TOK_WORD        toine 
**	token = TOK_DQUOTE      "     
**	token = TOK_NEWLINE           
**
**	token = TOK_WORD        echo
**	token = TOK_SPACE       
**	token = TOK_WORD        je \ suis an"toine
**	token = TOK_NEWLINE
*/

/*
**	TODO: if next char is not $ or " or \ or NEWLINE print \
*/

static void	expand_dquote_bslash(t_list **prev)
{
	t_list			*new;
	t_list			*tmp;
	t_list			*curr;
	t_token			*token;
	char			**str;

	tmp = (*prev)->next;
	curr = tmp->next;
	// boucle jusqu'a la dquote
	while (((t_token *)(curr->data))->type != TOK_DQUOTE && ((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		// si bslash
		if (((t_token *)(curr->data))->type == TOK_BSLASH)
		{
			// si next is NOT $ or " or '\'
			if ((((t_token *)(curr->next->data))->type != TOK_DOLLAR)
				&& (((t_token *)(curr->next->data))->type != TOK_DQUOTE)
				
				&& (((t_token *)(curr->next->data))->type != TOK_BSLASH))
			{	
				// créé TOK_WORD '\' 
				str = (char **)ft_calloc(1 + 1, sizeof(*str));
				if (!str)
					return ;
				*str = (char *)ft_calloc(1 + 1, sizeof(**str));
				if (!*str)
					return ;
				**str = '\\';
				token = token_init(TOK_WORD, str);
				new = ft_lstnew(token);
				// mette sur le prev donc avant le TOK_BSLASH
				new->next = curr;
				tmp->next = new;
				expand_bslash(&new, curr->next);
			}
			else
				expand_bslash(&tmp, curr->next);
			// expand_bslash
		}
		tmp = tmp->next;
		curr = curr->next;
	}
}

t_list	*expand_dquote(t_list **prev)
{
	t_list			*new;
	t_list			*next;
	t_token			*token;
	char			**str;

	expand_dquote_bslash(prev);
	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
		return (NULL);
	*str = (char *)ft_calloc(1 + 1, sizeof(**str));
	if (!*str)
		return (NULL);
	next = (*prev)->next->next;
	while (((t_token *)(next->data))->type != TOK_DQUOTE)
	{
		if (((t_token *)(next->data))->type == TOK_NEWLINE)
		{
			printf("Unexpected dquote\n");
			exit(EXIT_FAILURE);
		}
		*str = ft_strjoin(*str, *(((t_token *)(next->data))->data));
		next = next->next;
	}
	token = token_init(TOK_WORD, str);
	new = ft_lstnew(token);
	new->next = next->next;
	(*prev)->next = new;
	return (new);
}
