# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2025/01/15 02:40:57 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

INCLUDES = -I. -Ilibft/includes

LDLIBS = -Llibft -lft

OBJ_DIR = .obj

SRCS = main_readline.c

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: ftbranch libft $(OBJ_DIR) $(EXE)

$(EXE) :
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

minishell: $(SRCS:.c=.o)

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
