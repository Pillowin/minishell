/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/02 16:14:23 by agautier         ###   ########.fr       */
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

void	redir_merge(t_list *tokens)
{
	t_list	*curr;
	t_token	*redir;
	t_list	*tmp;
	char	**data;

	curr = tokens;
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
**	Check quotes error
**	And merge everyting in quotes (quotes included) into a t_token WORD
**
**	TOK_QUOTE -> TOK_BACKSLAH -> TOK_DQUOTE
*/

// void	interpret_quotes(t_list *tokens)
// {
// 	// Une liste avec pleins de tokens dont des TOK_[D]QUOTE

// 	// On transforme tout les tokens entre les quotes en un TOK_WORD

// 	// On veut une liste SANS TOK_[D]QUOTE
// }

/*
**	Update list
**
**	TODO: regrouper les tokens pour faire des t_command et t_redir
**	TODO: creer arbre
*/

void	parse_tokens(t_list **tokens)
{
	check_tokens(*tokens);
	expand(tokens);
	// redir_merge(tokens);
}
