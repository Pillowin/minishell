# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agautier <agautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 20:58:26 by agautier          #+#    #+#              #
#    Updated: 2021/03/14 20:02:55 by agautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO: norme because SRC need to be explicit
# TODO: remove fsanitize

NAME		=	minishell
SRC			=	$(wildcard $(addprefix src/, $(addsuffix .c, */*))) \
				$(wildcard $(addprefix src/, $(addsuffix .c, *)))
OBJ			=	$(SRC:.c=.o)
CC			=	gcc
HEADER		=	-Iheader -Ilibft/header
LIB			=	-Llibft
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(HEADER) $(LIB) -o $@ $(OBJ) -lft

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

libft:
	make -C libft

norme:
	norminette

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY:	all libft norme clean fclean re
