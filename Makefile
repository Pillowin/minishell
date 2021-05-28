# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 22:08:43 by mamaquig          #+#    #+#              #
#    Updated: 2021/05/13 20:5933 by mamaquig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO: remove fsanitize

NAME		=	minishell
SRC			=	$(addprefix src/,			\
					main.c					\
					minishell.c				\
				)\
				$(addprefix src/builtin/,	\
					cd.c					\
					echo.c					\
					env.c					\
					exit.c					\
					export.c				\
					pwd.c					\
					unset.c					\
				)\
				$(addprefix src/env/,		\
					env.c					\
					var.c					\
				)\
				$(addprefix src/error/,		\
					error.c					\
				)\
				$(addprefix src/exec/,		\
					binary_path.c			\
					binary.c				\
					builtin.c				\
					dispatch.c				\
					exec.c					\
					pipe.c					\
					redir.c					\
					tree_browse.c			\
				)\
				$(addprefix src/expansion/,	\
					expand_bslash.c			\
					expand_dollar_utils.c	\
					expand_dollar.c			\
					expand_dquote.c			\
					expand_quote.c			\
					expand.c				\
				)\
				$(addprefix src/lexer/,		\
					lexer_advance.c			\
					lexer.c					\
					token.c					\
				)\
				$(addprefix src/parser/,	\
					check_token.c			\
					command_merge.c			\
					eat_list.c				\
					parser.c				\
					redir_merge.c			\
					tree.c					\
				)\
				$(addprefix src/signal/,	\
					signal.c				\
				)\
				$(addprefix src/termcap/,	\
					termcap_key.c			\
					termcap_utils.c			\
					termcap.c				\
				)\
				$(addprefix src/utils/cmp/,	\
					cmp_tok_type.c			\
					cmp_var_name.c			\
				)\
				$(addprefix src/utils/,	\
					dlst_last.c				\
					ft_is_end_word.c		\
					ft_is_token.c			\
					ft_putchar.c			\
					ft_strslen.c			\
					is_name.c				\
					is_tok_type.c			\
					is_var.c				\
					lstdup.c				\
					waitall.c				\
				)
OBJ			=	$(SRC:.c=.o)
CC			=	gcc
HEADER		=	-Iheader -Ilibft/header
LIB			=	-Llibft
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(HEADER) $(LIB) -o $@ $(OBJ) -lft -ltermcap

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
