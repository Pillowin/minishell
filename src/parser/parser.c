/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/03/21 20:37:01 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	t_list *tokens                                                                    |
**	             0x0a                              0x0b                              0x0c                              0x0d
**	┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐
**	|                            |    |                            |    |                            |    |                            |
**	|  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |
**	|      - type = TOKEN_WORD   | -► |      - type = TOKEN_WORD   | -► |      - type = TOKEN_SEMI   | -► |      - type = TOKEN_WORD   |
**	|      - data = "echo"       |    |      - data = "antoine"    |    |      - data = ";"          |    |      - data = "ls"         |
**	|  - next = 0x0b             |    |  - next = 0x0c             |    |  - next = 0x0d             |    |  - next = NULL             |
**	|                            |    |                            |    |                            |    |                            |
**	└----------------------------┘    └----------------------------┘    └----------------------------┘    └----------------------------┘
*/

/*
**	Priorites:
**		- TOKEN_SEMI ;
**		- TOKEN_PIPE |
**		- TOKEN_DGREAT + TOKEN_WORD => TOKEN_REDIR [ >> , filename ]
**		- TOKEN_GREAT + TOKEN_WORD => TOKEN_REDIR [ > , filename ]
**		- TOKEN_LESS + TOKEN_WORD => TOKEN_REDIR [ < , filename ]
**		- TOKEN_WORD... => TOKEN_COMMAND [ TOKEN_WORD, TOKEN_WORD... ]
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
	const int		prios[5] = {TOKEN_SEMI, TOKEN_PIPE, TOKEN_DGREAT, TOKEN_GREAT, TOKEN_LESS};
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
**	Merge TOKEN_[LESS | GREAT | DGREAT] and TOKEN_WORD to TOKEN_REDIR
*/

void	redir_merge(t_list *tokens)
{
	t_list	*curr;
	t_token	*redir;
	t_list	*tmp;
	char	**data;

	curr = tokens;
	while (curr && ((t_token *)(curr->data))->type != TOKEN_NEWLINE)
	{
		if (((t_token *)(curr->data))->type == TOKEN_DGREAT
			|| ((t_token *)(curr->data))->type == TOKEN_GREAT
			|| ((t_token *)(curr->data))->type == TOKEN_LESS)
		{
			data = (char **)ft_calloc(2 + 1, sizeof(*data));
			if (!data)
				return ;
			data[0] = *(((t_token *)((curr)->data))->data);
			data[1] = *(((t_token *)((curr->next)->data))->data);
			redir = token_init(TOKEN_REDIR, data);
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
**	TODO: regrouper les tokens pour faire des t_command et t_redir
**	TODO: creer arbre
*/

/*
**	Update list
*/

void	parse_tokens(t_list *tokens)
{
	check_tokens(tokens);
	redir_merge(tokens);
}
