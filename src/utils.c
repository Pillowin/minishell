/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:59:09 by agautier          #+#    #+#             */
/*   Updated: 2021/04/11 18:39:556 by agautier         ###   ########.fr       */
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
int	my_strdup(char ***strs, size_t size, char *str)
{
	*strs = (char **)ft_calloc(size + 1, sizeof(**strs));
	if (!(*strs))
		return (FAILURE);
	*strs[0] = ft_strdup(str);
	if (!(*strs[0]))
	{
		ft_free((void **)&(*strs));
		return (FAILURE);
	}
	return (SUCCESS);
}

// /*
// **	Duplicate source but malloc'ed
// */
// char	**ft_strsdup(char **source)
// {
// 	unsigned int	i;
// 	char			**str;

// 	str = (char **)ft_calloc(ft_strslen(source) + 1, sizeof(*source));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (source[i])
// 	{
// 		str[i] = ft_strdup(source[i]);
// 		if (!str[i])
// 		{
// 			i--;
// 			while (i)
// 			{
// 				ft_free((void **)&str[i]);
// 				i--;
// 			}
// 			ft_free((void **)str);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (str);
// }

/*
**
*/

int	my_calloc(size_t count, size_t size, void **ptr)
{
	size_t	i;

	count++;
	*ptr = malloc(count * size);
	if (!*ptr)
		return (FAILURE);
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

t_dlist	*ft_create_delem(void *data)
{
	t_dlist	*list;

	list = (t_dlist *)malloc(sizeof(*list));
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

void	ft_dlist_push_back(t_dlist **begin_list, void *data)
{
	t_dlist	*curr;

	if (*begin_list == NULL)
	{
		*begin_list = ft_create_delem(data);
		return ;
	}
	curr = *begin_list;
	while (curr->next)
		curr = curr->next;
	curr->next = ft_create_delem(data);
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

void	waitall()
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

char	tab_init(char **s1, char **s2, char **s3)
{
	*s1 = ft_strdup(*s1);
	if (!*s1)
		return (FAILURE);
	*s2 = ft_strdup(*s2);
	if (!*s2)
	{
		ft_free((void **)s1);
		return (FAILURE);
	}
	*s3 = ft_strdup(*s3);
	if (!*s3)
	{
		ft_free((void **)s1);
		ft_free((void **)s2);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
**
*/

t_list	*update_env(t_list **env, char *name, char *value)
{
	t_list	*env_var;
	t_var	init;
	t_var	*var;

	env_var = ft_list_find(*env, (void *)name, &is_var);
	if (!env_var || !((t_var *)env_var->data)->value)
	{
		init.name = name;
		init.equal = "=";
		if (env_var && ((t_var *)env_var->data)->name)
			init.name = ((t_var *)env_var->data)->name;
		if (env_var && ((t_var *)env_var->data)->equal)
			init.equal = ((t_var *)env_var->data)->equal;
		init.value = value;
		if (!tab_init(&(init.name), &(init.equal), &(init.value)))
			return (NULL);
		var = var_init(init.name, init.equal, init.value);
		if (!var)
			return (NULL);
		ft_list_push_back(env, var);
		return(ft_lstlast(*env));
	}
	ft_free((void **)&((t_var *)env_var->data)->value);
	((t_var *)env_var->data)->value = value;
	return (env_var);
}
/*
**
*/

t_list	*insert_env(t_list **env, char *name, char *equal, char *value)
{
	t_var	*var;

	
	var = var_init(name, equal, value);
	if (!var)
		return (NULL);
	ft_list_push_back(env, var);
	return(ft_lstlast(*env));
}
