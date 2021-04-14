/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:38:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/04/14 23:26:32 by agautier         ###   ########.fr       */
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


static int	eat_list_elem(t_list *list, t_btree **node, t_err *err)
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
		if (!(*node))
		{
			// TODO:
			return ((long)error(err, MALLOC, NULL, NULL));
		}
		ft_free((void **)&(list));
		// return (SUCCESS);
	}
	else if (!prev)
	{
		*node = btree_create_node(((t_token *)(list->data)));
		if (!(*node))
		{
			// TODO:
			return ((long)error(err, MALLOC, NULL, NULL));
		}
		if (((t_token *)(list->data))->type == TOK_REDIR)
			left = list->next;
		else if (((t_token *)(list->data))->type == TOK_COMMAND)
			right = list->next;
		ft_free((void **)&(list));
		// return (SUCCESS);
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
		if (!(*node))
		{
			// TODO:
			return ((long)error(err, MALLOC, NULL, NULL));
		}
		ft_free((void **)&(prev->next));
	}
	if (left)
		if (!eat_list_elem(left, &((*node)->left), err))
			return (FAILURE);
	if (right)
		if (!eat_list_elem(right, &((*node)->right), err))
			return (FAILURE);
	return (SUCCESS);
}

int	create_tree(t_list *tokens, t_err *err)
{
	// TODO: segv when no input
	printf("\n-----------------------------------------\n");
	t_btree	*tree;

	ft_list_foreach(tokens, &token_print);
	printf("\n-----------------------------------------\n");
	printf("\tCreating tree\n\n");
	if (!tokens)
		return (FAILURE);
	if (!eat_list_elem(tokens, &tree, err))
		return (FAILURE);

	btree_apply_prefix(tree, &token_print);

	btree_apply_prefix(tree, &token_destroy);
	btree_free(&tree);
	return (SUCCESS);
}
