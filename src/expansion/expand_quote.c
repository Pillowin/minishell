/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:46:53 by agautier          #+#    #+#             */
/*   Updated: 2021/04/02 12:12:44 by agautier         ###   ########.fr       */
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
		*str = ft_strjoin(*str, *(((t_token *)(next->data))->data));
		next = next->next;
	}
	token = token_init(TOK_WORD, str);
	token_print(token);
	new = ft_lstnew(token);
	new->next = next->next;
	(*prev)->next = new;
	return (new);
	// free part list
}


/*
**	-----    -----    -----    -----    -----    -----    
**	| a | -> | P | -> | C | -> | N | -> | b | -> | c | -> 
**	-----    -----    -----    -----    -----    -----    
**
**	P->next = new
**	C = new
**	C->next = N
**
*/













// /*
// **	Interpret quote then update lexer->str
// **
// **	TODO: Error func when only one quote
// **	TODO: Malloc error
// */

// char	*expand_quote(t_lexer *lexer)
// {
// 	unsigned int	str_len;
// 	char			*ret;
// 	char			*str;

// 	ret = NULL;
// 	while (!ft_is_end_word(lexer->c))
// 	{
// 		str_len = 0;
// 		while (lexer->str[lexer->i + str_len] != '\'' && !ft_is_end_word(lexer->str[lexer->i + str_len]))
// 			str_len++;
// 		str = (char*)ft_calloc(str_len + 1, sizeof(*str));
// 		if (!str)
// 			return (NULL);
// 		str = ft_strncpy(str, &(lexer->str[lexer->i]), str_len);
// 		if (!ret)
// 			ret = str;
// 		else
// 		{
// 			ret = ft_strjoin(ret, str);
// 			ft_free((void **)&str);
// 		}
// 		lexer_advance(lexer, str_len);
// 		if (lexer->c == '\'')
// 		{
// 			str = get_char_in_quote(lexer);
// 			if (str)
// 			{
// 				ret = ft_strjoin(ret, str);
// 				ft_free((void **)&str);
// 			}
// 		}
// 	}
// 	return (ret);
// }

// /*
// **	Return string in quotes and position cursor on quote
// **	(lexer->c need to be on the first quote)
// **
// **	TODO: Error func when only one quote
// */

// char	*get_char_in_quote(t_lexer *lexer)
// {
// 	unsigned int	i;
// 	char			*str;

// 	i = 1;
// 	if (!ft_strchr(&(lexer->str[lexer->i + i]), '\''))
// 	{
// 		printf("Unexpected quote\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (lexer->str[lexer->i + i] != '\'')
// 		i++;
// 	str = (char*)ft_calloc(i, sizeof(*str));
// 	if (!str)
// 		return (NULL);
// 	str = ft_strncpy(str, &(lexer->str[lexer->i + 1]), i - 1);
// 	lexer_advance(lexer, i + 1);
// 	return (str);
// }
