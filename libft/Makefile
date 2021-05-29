# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agautier <agautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 12:52:43 by agautier          #+#    #+#              #
#    Updated: 2021/05/29 13:31:09 by agautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRC		=	$(addprefix src/, 				\
				tree/btree_create_node.c	\
				tree/btree_apply_prefix.c	\
				tree/btree_free.c			\
				\
				list/ft_create_elem.c		\
				list/ft_list_push_back.c	\
				list/ft_list_foreach.c		\
				list/ft_list_at.c			\
				list/ft_lstlast.c			\
				list/ft_list_find.c			\
				list/ft_list_sort.c			\
				list/ft_list_size.c			\
				list/ft_list_remove_if.c	\
				\
				gc/gc_btree_free.c			\
				gc/gc_calloc.c				\
				gc/gc_clean.c				\
				gc/gc_create_delem.c		\
				gc/gc_dlist_push_back.c		\
				gc/gc_free_tab.c			\
				gc/gc_free.c				\
				gc/gc_list_clear.c			\
				gc/gc_list_push_back.c		\
				gc/gc_list_remove_var.c		\
				gc/gc_lstnew.c				\
				gc/gc_lstdel.c				\
				gc/gc_lstdelone.c			\
				gc/gc_register.c			\
				gc/gc_strdup.c				\
				gc/gc_strjoin.c				\
				gc/gc_strsdup.c				\
				gc/gc_unregister.c			\
				gc/gc_list_foreach.c		\
				gc/gc_list_rm_tok_if.c		\
				gc/gc_btree_apply_prefix.c	\
				\
				is/ft_isalnum.c				\
				is/ft_isalpha.c				\
				is/ft_isprint.c				\
				is/ft_is_ll.c				\
				\
				memory/ft_calloc.c			\
				memory/ft_free.c			\
				memory/ft_memcpy.c			\
				\
				str/ft_atoi.c				\
				str/ft_itoa.c				\
				str/ft_split.c				\
				str/ft_strchr.c				\
				str/ft_strcmp.c				\
				str/ft_strdup.c				\
				str/ft_strlcat.c			\
				str/ft_strlen.c				\
				str/ft_strncpy.c			\
				str/ft_strncmp.c			\
				str/ft_substr.c				\
				\
				print/ft_putchar_fd.c		\
				print/ft_putendl_fd.c		\
				print/ft_putstr_fd.c		\
			)
OBJ		=	$(SRC:.c=.o)
HEADER	=	-Iheader -I../header
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar	rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
