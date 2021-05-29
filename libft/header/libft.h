/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:15:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/29 13:30:21 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_list.h"
# include "ft_btree.h"
# include "gc.h"
# include "minishell.h"

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_is_ll(const char *str);

void		*ft_calloc(size_t count, size_t size);
void		ft_free(void **ptr);
void		*ft_memcpy(void *dst, const void *src, size_t n);

int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);

#endif
