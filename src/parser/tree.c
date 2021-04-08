/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgmeqeeg <mgmeqeeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 21:49:04 by agautier          #+#    #+#             */
/*   Updated: 2021/04/07 16:14:402 bymgmiqeegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoie l’adresse de l'élément précedent le premier élément
**	dont la donnée comparée renvoie 0.
*/

static t_list	*ft_list_find_prev(t_list *begin_list, void *data_ref, int (*cmp)())
{
	t_list	*prev;

	prev = NULL;
	while (begin_list)
	{
		if (!cmp(begin_list->data, data_ref))
			return (prev);
		prev = begin_list;
		begin_list = begin_list->next;
	}
	return (NULL);
}

static t_list *find_next(t_list *tokens)
{
	t_list	*ret;

	ret = ft_list_find_prev(tokens, (void *)TOK_SEMI, &is_tok_type);
	if (ret)
		return (ret);
	ret = ft_list_find_prev(tokens, (void *)TOK_PIPE, &is_tok_type);
	if (ret)
		return (ret);
	ret = ft_list_find_prev(tokens, (void *)TOK_REDIR, &is_tok_type);
	if (ret)
		return (ret);
	return (NULL);
}


static void	eat_list_elem(t_list *list, t_btree **node)
{
	t_list	*left;
	t_list	*right;
	t_list	*prev;

	left = NULL;
	right = NULL;
	prev = find_next(list);
	if (!prev && !(list->next))
	{
		*node = btree_create_node(((t_token *)(list->data)));
		ft_free((void **)&(list));
		return ;
	}
	else if (!prev)
	{
		*node = btree_create_node(((t_token *)(list->data)));
		if (((t_token *)(list->data))->type == TOK_REDIR)
			left = list->next;
		else if (((t_token *)(list->data))->type == TOK_COMMAND)
			right = list->next;
		ft_free((void **)&(list));
	}
	else
	{
		if (((t_token *)(prev->next->data))->type == TOK_SEMI
			|| ((t_token *)(prev->next->data))->type == TOK_PIPE)
		{
			left = list;
			right = prev->next->next;
		}
		else if (((t_token *)(prev->next->data))->type == TOK_REDIR)
		{
			right = list;
			left = prev->next->next;
		}
		*node = btree_create_node(((t_token *)(prev->next->data)));
		ft_free((void **)&(prev->next));
	}
	if (left)
		eat_list_elem(left, &((*node)->left));
	if (right)
		eat_list_elem(right, &((*node)->right));
}

void	create_tree(t_list *tokens)
{
	printf("\n-----------------------------------------\n");
	printf("\tCreating tree\n\n");
	t_btree	*tree;

	ft_list_remove_if(&tokens, (void *)TOK_NEWLINE, &is_tok_type, &ft_free);
	eat_list_elem(tokens, &tree);

	printf("\n-----------------------------------------\n");
	btree_apply_prefix(tree, &token_print);
	btree_free(&tree);
}


/*
ls -l | grep grw | wc -l > lsfile ; < lsfile cat | rev > itit > utut >> otot ; diff otot toto >> diff
	- echo toto     ;    ls -l    |      grep drw
	-    cmd      semi    cmd    pipe      cmd

		- recup next node et creer =  ;
			=> list_gauche = cmd
				- recup next node et creer =  cmd
					=>
					=>
			=> list_droite = cmd pipe cmd
				- recup next node et creer =  |
					=> list_gauche = cmd
						- recup next node et creer =  cmd
							=>
							=>
					=> list_droite = cmd
						- recup next node et creer =  cmd
							=>
							=>
	---	semi ---
	|          |
	cmd      -- pipe --
			|        |
				cmd       cmd
*/




























// static void	add_semi(t_list *tokens, int index)
// {
// 	// si find_xxx < index
// 		// add a gauche
// 		// apply_priority
// 	// else
// 		// add a gauche
// }

// static void	apply_priority()
// {
// 	add_semi(tokens);
// 	add_pipe(tokens);
// 	add_redir(tokens);
// 	add_command(tokens);
// }
