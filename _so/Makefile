# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaret <souaret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 22:08:36 by souaret           #+#    #+#              #
#    Updated: 2025/01/27 20:59:07 by souaret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell_so

LIBFT_D =../libft
LIBFT   = $(LIBFT_D)/libft.a
INCLIBFT= $(LIBFT_D)/includes

INCH	=	-I .	\
			-I../	\
			-I$(INCLIBFT)

SRCH	=	minishell_so.h

SRCtoken	=	system_utils.c 	\
			tokens_utils.c 		tree_sample_echo.c  \
			main_so.c

SRCS	=	../system_utils.c 	../cmd_utils.c ../cmd_utils2.c 	../cmd_exec.c 	\
			tst_main_1.c

#OBJS:= $(SRCS:.c=.o)
OBJ_DIR = .obj

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCH) $< -o $@
	@mv *.o $(OBJ_DIR)

.obj:
	@mkdir -p .obj

#OBJS:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS:= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
	

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -I ../
LFLAGS = -L $(LIBFT_D) -lft 

#%.o : %.c 
#	$(CC) -c $(CFLAGS) $(INCH) $< -o $@

#	$(CC) $(CFLAGS) $(INCH) -c $<

all : $(NAME) $(LIBFT)  $(OBJ_DIR)  $(NAME)
	
$(NAME) : $(SRCS) $(SRCH) $(OBJ_DIR) $(LIBFT)
	echo "OBJ=" $(OBJ_DIR)
	echo "SRCS=" $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS)  -o $@ 
# $(NAME) : $(SRCS) $(SRCH) $(OBJS) $(LIBFT)
# 	echo $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS)  -o $@ 

minishell_so: $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

$(LIBFT) : 
	make -C $(LIBFT_D)

clean :
	@rm -f $(OBJS) $(OBJSB)
	@make -C $(LIBFT_D) clean

fclean : clean
	@rm -f $(NAME) fractol_bonus
	@make -C $(LIBFT_D) fclean

re : fclean all

norm:  $(NAME)
	norminette *.[ch] libft/

#-----------------------------------------------------------------------------

#--- Mandatory Variables #
.PHONY : all clean fclean re
