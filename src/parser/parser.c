/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeeteer <ggeeteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/04/08 17:14:563 byggieteerr         ###   ########.fr       */
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
	void			(*const check_f[5])(t_list*, unsigned int) = {check_semi, check_pipe, check_dgreat, check_great, check_less};
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
	t_list	*redir;
	t_list	*prev;
	char	**data;

	prev = NULL;
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
			data[0] = ft_strdup(*(((t_token *)((curr)->data))->data));
			data[1] = ft_strdup(*(((t_token *)((curr->next)->data))->data));
			redir = ft_lstnew(token_init(TOK_REDIR, data));
			redir->next = curr->next->next;
			if (prev)
				prev->next = redir;
			else
				*tokens = redir;
			ft_lstdelone(curr->next, token_destroy);
			ft_lstdelone(curr, token_destroy);
			curr = redir;
		}
		if (curr->next)
			prev = curr;
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
	t_list			*tmp;
	t_list			*redirs;
	char			**str;
	unsigned int	i;

	curr = *tokens;
	prev = NULL;
	while (((t_token *)(curr->data))->type != TOK_NEWLINE)
	{
		redirs = NULL;
		i = 0;
		if (((t_token *)(curr->data))->type == TOK_WORD)
		{
			str = (char **)ft_calloc(128 * 128, sizeof(str));	// TODO: count word
			while (((t_token *)(curr->data))->type == TOK_WORD || ((t_token *)(curr->data))->type == TOK_REDIR)
			{
				if (((t_token *)(curr->data))->type == TOK_REDIR)
				{
					if (!redirs)
						redirs = ft_lstnew(curr->data);
					else
						ft_lstlast(redirs)->next = ft_lstnew(curr->data);
					tmp = curr->next;
					ft_lstdelone(curr, NULL);
					curr = tmp;
					continue;
				}
				str[i] = ft_strdup(*(((t_token *)(curr->data))->data));
				tmp = curr->next;
				ft_lstdelone(curr, &token_destroy);
				curr = tmp;
				i++;
			}
			new = ft_lstnew(token_init(TOK_COMMAND, str));
			if (redirs)
			{
				new->next = redirs;
				ft_lstlast(redirs)->next = curr;
			}
			else
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
	printf("\n-----------------------------------------\n\tCreating list\n\n");
	ft_list_foreach(*tokens, &token_print);
	command_merge(tokens);
	printf("\n-----------------------------------------\n\tCommand merged\n\n");
	ft_list_foreach(*tokens, &token_print);
	ft_list_remove_if(tokens, (void *)TOK_NEWLINE, &is_tok_type, &token_destroy);
	create_tree(*tokens);
}
