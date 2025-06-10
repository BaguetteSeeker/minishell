# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2025/06/10 16:28:07 by anle-pag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

ASAN = -fsanitize=address -g

INCLUDES = -I. -Iincludes/ -Ilibft/includes

LDLIBS = -Llibft -lft -L/usr/lib/x86_64-linux-gnu -lreadline

OBJ_DIR = .obj

SRCS =	minishell.c prompt.c cleanup_utils.c repl.c cleanup_utils2.c \
		parsing/parser.c \
		parsing/heredoc.c\
		parsing/lexer.c parsing/parser_utils.c \
		expansion/expansion.c \
		expansion/exp_list.c expansion/exp_list_utils.c \
		expansion/exp_varexp.c expansion/exp_varexp_utils.c\
		expansion/exp_segment.c expansion/exp_segment_utils.c\
		expansion/exp_assign.c expansion/exp_redirection.c \
		expansion/exp_heredoc.c expansion/exp_heredoc_utils.c \
		expansion/exp_wildcard.c \
		exec/exec.c \
		exec/exec_pipes.c exec/exec_utils.c exec/redirs.c \
		exec/exec_command.c \
		built-ins/builtins.c \
		built-ins/builtins_echo.c built-ins/builtins_export.c \
		built-ins/builtins.c built-ins/builtins_cd.c \
		built-ins/builtins_misc.c \
		shell/shell_env.c \
		shell/shell_assign.c shell/shell_env_utils.c \
		shell/shell_mode.c shell/shell_var.c signals.c \
		shell/shell_variable_interface.c  \
		debug/draw_ast.c debug/putlogs.c debug/exp_debugger.c

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
	@mkdir -p .obj/parsing .obj/expansion .obj/exec .obj/built-ins .obj/shell .obj/debug

clean:
	@rm -f $(EXE)
	@make clean -C libft

fclean:  clean
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: ftbranch fclean relibft $(OBJ_DIR) $(EXE)

.PHONY:  all clean fclean re libft relibft
