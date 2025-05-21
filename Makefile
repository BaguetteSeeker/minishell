# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2025/05/12 13:16:04 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

ASAN = -fsanitize=address -g

INCLUDES = -I. -Iincludes/ -Ilibft/includes

LDLIBS = -Llibft -lft -L/usr/lib/x86_64-linux-gnu -lreadline

OBJ_DIR = .obj

SRCS = minishell.c lexer.c heredoc.c parser.c parser_utils.c \
		expander.c expander_utils.c expand_callers.c \
		cleanup_utils.c signals.c putlogs.c prompt.c \
		draw_ast.c exec.c exec_utils.c exec_pipes.c \
		redirs.c

$(OBJ_DIR)/%.o : srcs/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: ftbranch libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

minishell: $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

libft:
	@make -C libft

relibft:
	@make re -C libft

ftbranch:
	@git -C libft checkout main

.obj:
	@mkdir -p .obj

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: ftbranch fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re libft relibft
