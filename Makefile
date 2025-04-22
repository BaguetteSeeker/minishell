# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaret <souaret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2025/04/22 14:46:02 by souaret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

INCLUDES = -I. -Iincludes/ -Ilibft/includes

LDLIBS = -Llibft -lft -L/usr/lib/x86_64-linux-gnu -lreadline

OBJ_DIR = .obj

SRCS = lexer.c parser.c \
		builtin.c 	builtin2.c 	cmd_pipe.c 	cmd_tree.c 	\
		cmd_exec.c 	cmd_exec2.c 	cmd_utils.c 	cmd_utils2.c \
		file_utils.c  system_utils.c  \
		main_exec.c
#		main_readline.c 

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
