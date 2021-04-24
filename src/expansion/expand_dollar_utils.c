/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:15:54 by agautier          #+#    #+#             */
/*   Updated: 2021/04/24 20:47:07 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Extract name from word
*/

char	*fetch_name(char **word)
{
	unsigned int	i;
	char			*name;
	void			*tmp;

	i = 0;
	if (ft_isalpha((*word)[i]) && (*word)[i] != '_')
	{
		i++;
		while ((*word)[i] && (ft_isalnum((*word)[i]) || (*word)[i] == '_'))
			i++;
	}
	name = ft_substr(*word, 0, i);
	if (!name)
	{
		return (NULL);//TODO: err malloc
	}
	tmp = *word;
	*word = ft_substr(*word, i, ft_strlen(*word) - i);
	ft_free(&tmp);
	if (!(*word))
	{
		return (NULL);//TODO: err malloc
	}
	return (name);
}

/*
**	Create a new list elem with TOK_SPACE as data
*/

static char	new_lst_space(t_list **new, t_err *err)
{
	char	**data;

	if (!my_strdup(&data, 1, " "))
		return ((char)error(err, MALLOC, NULL, NULL));
	if (!new_lstok(TOK_SPACE, data, new))
		return ((char)error(err, MALLOC, NULL, NULL));
	return (SUCCESS);
}

/*
**	Convert char * to list with only TOK_SPACE and TOK_WORD
*/

static t_list	*value_to_lst(char *value, t_err *err)
{
	t_list	*new;
	t_lexer	*lexer;
	t_token	*token;

	if (!lexer_init(value, &lexer))
		return (error(err, MALLOC, NULL, NULL));
	new = NULL;
	while (lexer->i < lexer->str_len)
	{
		if (lexer->c == ' ')
			token = lexer_advance_current(lexer, TOK_SPACE, err);
		else
			token = lexer_advance_word(lexer, err);
		if (!token)
		{
			ft_lstdel((void **)&new);
			ft_free((void **)&(lexer));
			return (FAILURE);
		}
		ft_list_push_back(&new, token);
	}
	ft_free((void **)&(lexer));
	if (!new)
		new_lst_space(&new, err);
	return (new);
}

/*
**	Fetch value from name
*/

t_list	*fetch_value(t_list *next, char *name, t_list *env, t_err *err)
{
	t_list	*new;
	t_list	*value;

	value = ft_list_find(env, (void *)name, &is_var);
	new = next;
	if (value)
	{
		new = value_to_lst(((t_var *)(value)->data)->value, err);
		if (!new)
			return (NULL);	// TODO: error malloc
		if (!ft_strcmp(name, *(((t_token *)(next->data))->data)))
			ft_lstlast(new)->next = next->next;
		else
			ft_lstlast(new)->next = next;
	}
	else if (!ft_strcmp(name, *(((t_token *)(next->data))->data)))
		new = next->next;
	return (new);
}
