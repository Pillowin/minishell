/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggieteer <ggieteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:45:29 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 20:11:316 byggtiteerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// /*
// **
// */

// static int	cmp(void *data, void *ref)
// {
// 	if (data == ref)
// 		return (0);
// 	return (1);
// }

// /*
// **
// */
// void	gc_unregister(t_list **gc, void *ptr)
// {
// 	if (!ptr)
// 		return ;
// 	ft_list_remove_if(gc, ptr, &cmp, NULL);
// }

/*
**
*/

void	gc_list_push_back(t_list **begin_list, void *data, t_list **gc)
{
	t_list	*current;

	if (*begin_list == NULL)
	{
		*begin_list = ft_create_elem(data);
		gc_register(gc, *begin_list);
		return ;
	}
	current = *begin_list;
	while (current->next)
		current = current->next;
	current->next = ft_create_elem(data);
	gc_register(gc, current->next);
}

/*
**
*/

void	gc_list_clear(t_list *begin_list, t_list **gc)
{
	t_list	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		gc_free(gc, (void **)&begin_list);
		begin_list = tmp;
	}
}

/*
**
*/

void	gc_list_foreach(t_list *begin_list, void (*f)(void *, t_list **), t_list **gc)
{
	while (begin_list)
	{
		(*f)(begin_list->data, gc);
		begin_list = begin_list->next;
	}
}

/*
**
*/

void	gc_list_remove_var(t_list **begin_list, void *data_ref, t_list **gc)
{
	t_list	*list_ptr;
	t_list	*prev;

	list_ptr = *begin_list;
	prev = NULL;
	while (list_ptr)
	{
		if (!ft_strcmp(((t_var *)list_ptr->data)->name, data_ref))
		{
			if (prev)
				prev->next = list_ptr->next;
			else
				*begin_list = (*begin_list)->next;
			var_destroy(list_ptr->data, gc);
			ft_free((void **)&list_ptr);
			if (!prev)
				list_ptr = (*begin_list);
			else
				list_ptr = prev->next;
			continue ;
		}
		prev = list_ptr;
		list_ptr = list_ptr->next;
	}
}

/*
**
*/

void	gc_list_rm_tok_if(t_list **begin_list, void *data_ref,
							int (*cmp)(), t_list **gc)
{
	t_list	*list_ptr;
	t_list	*prev;

	list_ptr = *begin_list;
	prev = NULL;
	while (list_ptr)
	{
		if (!cmp(list_ptr->data, data_ref))
		{
			if (prev)
				prev->next = list_ptr->next;
			else
				*begin_list = (*begin_list)->next;
			token_destroy(list_ptr->data, gc);
			gc_free(gc, (void **)&list_ptr);
			if (!prev)
				list_ptr = (*begin_list);
			else
				list_ptr = prev->next;
			continue ;
		}
		prev = list_ptr;
		list_ptr = list_ptr->next;
	}
}

/*
**
*/

void	gc_lstdelone(t_list *lst, void (*del)(void *, t_list **), t_list **gc)
{
	if (!lst)
		return ;
	if (del)
		del(lst->data, gc);
	gc_free(gc, (void **)&lst);
}

/*
**	Alloc strs then strdup str in *strs
*/

int	gc_strsdup(char ***strs, size_t size, char *str, t_list **gc)
{
	*strs = (char **)gc_calloc(gc, size + 1, sizeof(**strs));
	if (!(*strs))
		return (FAILURE);
	*strs[0] = ft_strdup(str);
	if (!(*strs[0]))
		return (FAILURE);
	gc_register(gc, **strs);
	return (SUCCESS);
}


void	gc_btree_free(t_btree **root, t_list **gc)
{
	if (!(*root))
		return ;
	gc_btree_free(&((*root)->left), gc);
	gc_btree_free(&((*root)->right), gc);
	gc_free(gc, (void **)&(*root));
}

void	gc_btree_apply_prefix(t_btree *root, void (*applyf)(void *, t_list **), t_list **gc)
{
	if (!root)
		return ;
	applyf(root->item, gc);
	gc_btree_apply_prefix(root->left, applyf, gc);
	gc_btree_apply_prefix(root->right, applyf, gc);
}
