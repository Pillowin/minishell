/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:46:53 by agautier          #+#    #+#             */
/*   Updated: 2021/04/03 16:00:54 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	token = TOK_WORD        echo  
**	token = TOK_SPACE             
**	token = TOK_WORD        je    
**	token = TOK_SPACE             <-- previous de expand.c, passé en paramètre à expand_quote
**	token = TOK_QUOTE       '     <-- curr de expand.c
**	token = TOK_WORD        suis  <-- next de expand.c, passé en paramètre à expand_quote
**	token = TOK_SPACE             
**	token = TOK_WORD        an    
**	token = TOK_QUOTE       '     
**	token = TOK_WORD        toine 
**	token = TOK_NEWLINE           
*/

t_list	*expand_quote(t_list **prev, t_list *next)
{
	t_list			*new;
	t_token			*token;
	char			**str;

	str = (char **)ft_calloc(1 + 1, sizeof(*str));
	if (!str)
		return (NULL);
	*str = (char *)ft_calloc(1 + 1, sizeof(**str));
	if (!*str)
		return (NULL);
	while (((t_token *)(next->data))->type != TOK_QUOTE)
	{
		if (((t_token *)(next->data))->type == TOK_NEWLINE)
		{
			printf("Unexpected quote\n");
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
