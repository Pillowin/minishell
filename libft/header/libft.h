/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:15:19 by agautier          #+#    #+#             */
/*   Updated: 2021/05/13 16:14:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_list.h"
# include "ft_btree.h"
# include "get_next_line.h"
# include "gc.h"

int		ft_isalnum(int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	ft_free(void **ptr);
char	*ft_strchr(const char *s, int c);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstnew(void *data);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr(char *str);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		ft_isprint(int c);
void	ft_bzero(void *s, size_t n);

#endif
