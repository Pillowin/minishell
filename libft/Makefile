# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agautier <agautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 12:52:43 by agautier          #+#    #+#              #
#    Updated: 2021/05/13 16:15:09 by agautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRC		=	$(addprefix src/, \
				ft_isalnum.c \
				ft_calloc.c \
				ft_strlen.c \
				ft_create_elem.c \
				ft_free.c \
				ft_strchr.c \
				ft_strncpy.c \
				ft_strjoin.c \
				ft_strcpy.c \
				ft_strcmp.c \
				ft_strlcat.c \
				ft_memcpy.c \
				ft_putstr.c \
				ft_strdup.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_strncmp.c \
				ft_isalpha.c \
				ft_isalnum.c \
				ft_substr.c \
				ft_putchar_fd.c \
				ft_split.c \
				ft_itoa.c	\
				get_next_line_utils.c \
				get_next_line.c \
				ft_isprint.c \
				ft_bzero.c \
				gc.c \
				\
				ft_list_push_back.c \
				ft_list_foreach.c \
				ft_list_at.c \
				ft_lstnew.c \
				my_list_foreach_if.c \
				ft_list_remove_if.c \
				ft_list_find.c \
				ft_list_clear.c \
				ft_lstlast.c \
				ft_lstdelone.c \
				ft_list_push_strs.c \
				ft_list_sort.c \
				ft_list_size.c \
				\
				btree_create_node.c \
				btree_apply_prefix.c \
				btree_free.c)
OBJ		=	$(SRC:.c=.o)
HEADER	=	header
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
