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

SRCS =	minishell.c prompt.c cleanup_utils.c \
		parsing/parser.c \
		parsing/expand_callers.c parsing/expander.c \
		parsing/expander_utils.c parsing/heredoc.c\
		parsing/lexer.c parsing/parser_utils.c \
		exec/exec.c \
		exec/exec_pipes.c exec/exec_utils.c exec/redirs.c \
		built-ins/builtins.c \
		built-ins/builtins_echo.c built-ins/builtins_exset.c \
		built-ins/builtins.c built-ins/builtins_cd.c \
		built-ins/builtins_misc.c \
		shell/shell_env.c \
		shell/shell_env_interface.c shell/shell_env_utils.c \
		shell/shell_mode.c shell/shell_var.c shell/signals.c \
		debug/draw_ast.c debug/putlogs.c repl.c 

$(OBJ_DIR)/%.o : srcs/%.c
	$(CC) -c $(CFLAGS) $(ASAN) $(INCLUDES) $< -o $@

all: ftbranch libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $(ASAN) $^ -o $@ $(LDLIBS)
#$(ASAN) 

minishell: $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

libft:
	@make -C libft

relibft:
	@make re -C libft

ftbranch:
	@git -C libft checkout main

.obj:
	@mkdir -p .obj/parsing .obj/exec .obj/built-ins .obj/shell .obj/debug

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: ftbranch fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re libft relibft
