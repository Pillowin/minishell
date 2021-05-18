/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiteer <gguiteer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:59:09 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 18:39:566 byagattierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	 Return 1 if c is a space or a \n else return 0
*/

int	ft_is_end_word(char c)
{
	if (!c || c == ' ' || c == '\n')
		return (1);
	return (0);
}

/*
**	Return 1 if c is a token else return 0
*/

int	ft_is_token(char c)
{
	if (c == ' '
		|| c == '\n'
		|| c == '\\'
		|| c == '\''
		|| c == '"'
		|| c == '$'
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == ';')
		return (1);
	return (0);
}

/*
**	Return 0 if type == data->type
*/

int	is_tok_type(t_token *data, void *type)
{
	if (data->type == (long)type)
		return (0);
	return (1);
}

/*
**
*/

int	my_calloc(size_t count, size_t size, void **ptr, t_list **gc)
{
	size_t	i;

	count++;
	*ptr = malloc(count * size);
	if (!*ptr)
		return (FAILURE);
	gc_register(gc, *ptr);
	i = 0;
	while (i < size * count)
	{
		((unsigned char *)(*ptr))[i] = '\0';
		i++;
	}
	return (SUCCESS);
}

// TODO: put in libft
size_t	ft_strslen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

/*
**	Use to find var in env
*/
int	is_var(void *data, void *ref)
{
	if (!ft_strcmp(((t_var *)data)->name, ref))
		return (0);
	return (1);
}

/*
**	check if word is a name until delimiter
*/
char	is_name(char *word, char delimiter)
{
	unsigned int	i;

	if (!word)
		return (FAILURE);
	i = 0;
	if (!ft_isalpha(word[i]) && word[i] != '_')
		return (FAILURE);
	i++;
	while (word[i] && word[i] != delimiter)
	{
		if (!ft_isalnum(word[i]) && word[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
** create new double list
*/

t_dlist	*gc_create_delem(t_list **gc, void *data)
{
	t_dlist	*list;

	list = (t_dlist *)gc_calloc(gc, 1, sizeof(*list));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

/*
**	push back new double list
*/

void	gc_dlist_push_back(t_list **gc, t_dlist **begin_list, void *data)
{
	t_dlist	*curr;

	if (*begin_list == NULL)
	{
		*begin_list = gc_create_delem(gc, data);
		return ;
	}
	curr = *begin_list;
	while (curr->next)
		curr = curr->next;
	curr->next = gc_create_delem(gc, data);
	curr->next->prev = curr;
}

/*
**	
*/

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/*
**
*/

t_dlist	*dlst_last(t_dlist *dlist)
{
	while (dlist && dlist->next)
		dlist = dlist->next;
	return (dlist);
}

/*
**	Wait until all child are DEAD :3
*/

void	waitall(void)
{

	int ret;

	while (1)
	{
		ret = waitpid(-1, NULL, 0);
		if (ret == -1)
			break;
	}
}

/*
**	Create t to create a new var.
*/

char	tab_init(char **s1, char **s2, char **s3, t_list **gc)
{
	*s1 = ft_strdup(*s1);
	if (!*s1)
		return (FAILURE);
	gc_register(gc, *s1);	
	*s2 = ft_strdup(*s2);
	if (!*s2)
	{
		gc_free(gc, (void **)s1);
		return (FAILURE);
	}
	gc_register(gc, *s2);
	*s3 = ft_strdup(*s3);
	if (!*s3)
	{
		gc_free(gc, (void **)s1);
		gc_free(gc, (void **)s2);
		return (FAILURE);
	}
	gc_register(gc, *s3);	
	return (SUCCESS);
}

// // TODO: delete
// void	var_print(void *data)
// {
// 	t_var	*var;

// 	var = (t_var *)data;
// 	fprintf(stderr, "var = {%s %s %s}\n", var->name, var->equal, var->value);
// }
