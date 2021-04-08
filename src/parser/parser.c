/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/07 18:41:32 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	t_list *tokens                                                                    |
**	             0x0a                              0x0b                              0x0c                              0x0d
**	┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐
**	|                            |    |                            |    |                            |    |                            |
**	|  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |
**	|      - type = TOK_WORD     | -► |      - type = TOK_WORD     | -► |      - type = TOK_SEMI     | -► |      - type = TOK_WORD     |
**	|      - data = "echo"       |    |      - data = "antoine"    |    |      - data = ";"          |    |      - data = "ls"         |
**	|  - next = 0x0b             |    |  - next = 0x0c             |    |  - next = 0x0d             |    |  - next = NULL             |
**	|                            |    |                            |    |                            |    |                            |
**	└----------------------------┘    └----------------------------┘    └----------------------------┘    └----------------------------┘
*/

/*
**	Priorites:
**		- TOK_SEMI ;
**		- TOK_PIPE |
**		- TOK_DGREAT + TOK_WORD => TOK_REDIR [ >> , filename ]
**		- TOK_GREAT + TOK_WORD => TOK_REDIR [ > , filename ]
**		- TOK_LESS + TOK_WORD => TOK_REDIR [ < , filename ]
**		- TOK_WORD... => TOK_COMMAND [ TOK_WORD, TOK_WORD... ]
*/

/*
**	Comparer l'enum avec les éléments (token) du tableau.
*/

static int	cmp_lstdata_data(t_token *lstdata, int *data)
{
	if ((int)(lstdata->type) == *data)
		return (0);
	return (1);
}

/*
**	Syntax check for each token.
*/

void	check_tokens(t_list *tokens)
{
	const int		prios[5] = {TOK_SEMI, TOK_PIPE, TOK_DGREAT, TOK_GREAT, TOK_LESS};
	void			(*const check_f[5])(t_list*, void*, unsigned int) = {check_semi, check_pipe, check_dgreat, check_great, check_less};
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		my_list_foreach_if(tokens, check_f[i], (void *)&(prios[i]), cmp_lstdata_data);
		i++;
	}
}

/*
**	Merge TOK_[LESS | GREAT | DGREAT] and TOK_WORD to TOK_REDIR
*/

void	redir_merge(t_list **tokens)
{
	t_list	*curr;
	t_token	*redir;
	t_list	*tmp;
	char	**data;

	curr = *tokens;
	while (curr && ((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		if (((t_token *)(curr->data))->type == TOK_DGREAT
			|| ((t_token *)(curr->data))->type == TOK_GREAT
			|| ((t_token *)(curr->data))->type == TOK_LESS)
		{
			data = (char **)ft_calloc(2 + 1, sizeof(*data));
			if (!data)
				return ;
			data[0] = *(((t_token *)((curr)->data))->data);
			data[1] = *(((t_token *)((curr->next)->data))->data);
			redir = token_init(TOK_REDIR, data);
			if (redir)
			{
				tmp = curr->next->next;
				// ft_free(&(curr->next->data));
				// ft_free(&(curr->next));
				curr->next = tmp;
				// ft_free(&(curr->data));
				curr->data = redir;
			}
		}
		curr = curr->next;
	}
}

/*
**	Merge all TOK_WORD qui se suivent
*/

void	command_merge(t_list **tokens)	// TODO: ignorer les tok_redir
{
	t_list			*curr;
	t_list			*prev;
	t_list			*new;
	t_token			*command;
	char			**str;
	unsigned int	i;

	curr = *tokens;
	prev = NULL;
	while (((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		i = 0;
		if (((t_token *)(curr->data))->type == TOK_WORD)
		{
			str = (char **)ft_calloc(128 * 128, sizeof(str));	// TODO: count word
			while (((t_token *)(curr->data))->type == TOK_WORD)
			{
				// str[i] = (char *)ft_calloc(128, sizeof(*str));
				// str = (char **)realloc(str, (1 * sizeof(str)));
				str[i] = ft_strdup(*(((t_token *)(curr->data))->data));
				// delete curr
				curr = curr->next;
				// if (!prev)
				// 	curr = *tokens;
				// else
				// 	curr = prev->next;
				i++;
			}
			command = token_init(TOK_COMMAND, str);
			new = ft_lstnew(command);
			new->next = curr;
			if (!prev)
				*tokens = new;
			else
				prev->next = new;
			continue ;
		}
		if (curr->next)
			prev = curr;
		curr = curr->next;
	}
}


/*
**	Update list
**
**	TODO: regrouper les tokens pour faire des t_command et t_redir
**	TODO: creer arbre
*/

void	parse_tokens(t_list **tokens)
{
	expand(tokens);
	check_tokens(*tokens);
	redir_merge(tokens);
	// ft_list_foreach(*tokens, &token_print);
	printf("\n-----------------------------------------\n\tCreating list\n\n");
	command_merge(tokens);
	ft_list_foreach(*tokens, &token_print);

	create_tree(*tokens);
}
