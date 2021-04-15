/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:46:34 by agautier          #+#    #+#             */
/*   Updated: 2021/04/15 16:46:49 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoie l’adresse de l'élément précedent le premier élément
**	dont la donnée comparée renvoie 0.
*/

static t_list	*ft_list_find_prev(t_list *list, void *data_ref, int (*cmp)())
{
	t_list	*prev;

	prev = NULL;
	while (list)
	{
		if (!cmp(list->data, data_ref))
			return (prev);
		prev = list;
		list = list->next;
	}
	return (NULL);
}

/*
**	Trouve le token suivant dans la liste par ordre de priorité
*/

static t_list	*find_next(t_list *tokens)
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

/*
**	
*/

static int	create_node_no_prio(t_list *list, t_btree **node, t_child *child)
{
	*node = btree_create_node(((t_token *)(list->data)));
	if (!(*node))
		return (FAILURE);
	if (list->next && ((t_token *)(list->data))->type == TOK_REDIR)
		child->left = list->next;
	else if (list->next && ((t_token *)(list->data))->type == TOK_COMMAND)
		child->right = list->next;
	ft_free((void **)&(list));
	return (SUCCESS);
}

/*
**
*/

static int	create_node_prio(t_list *list, t_list *prev, t_btree **node,
								t_child *child)
{
	if (((t_token *)(prev->next->data))->type == TOK_SEMI
		|| ((t_token *)(prev->next->data))->type == TOK_PIPE)
	{
		child->left = list;
		child->right = prev->next->next;
	}
	else if (((t_token *)(prev->next->data))->type == TOK_REDIR)
	{
		child->right = list;
		child->left = prev->next->next;
	}
	*node = btree_create_node(((t_token *)(prev->next->data)));
	if (!(*node))
		return (FAILURE);
	ft_free((void **)&(prev->next));
	return (SUCCESS);
}

/*
**	Fonction récursive
**	On créé un arbre à partir d'une liste
*/

int	eat_list(t_list *list, t_btree **node)
{
	t_child	child;
	t_list	*prev;

	child.left = NULL;
	child.right = NULL;
	prev = find_next(list);
	if (!prev)
		if (!create_node_no_prio(list, node, &child))
			return (FAILURE);
	if (prev)
		if (!create_node_prio(list, prev, node, &child))
			return (FAILURE);
	if (child.left)
		if (!eat_list(child.left, &((*node)->left)))
			return (FAILURE);
	if (child.right)
		if (!eat_list(child.right, &((*node)->right)))
			return (FAILURE);
	return (SUCCESS);
}
