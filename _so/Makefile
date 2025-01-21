# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaret <souaret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 22:08:36 by souaret           #+#    #+#              #
#    Updated: 2025/01/21 19:10:30 by souaret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell_so

LIBFT_D =../libft
LIBFT   = $(LIBFT_D)/libft.a
INCLIBFT= $(LIBFT_D)/includes

INCH	=	-I.	\
			-I$(INCLIBFT)	\

SRCH	=	minishell_so.h

SRCS	=	system_utils.c  tokens_utils.c  \
			tree_sample_echo.c  tree_samples.c	\
			main_so.c

OBJS:= $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LFLAGS = -L $(LIBFT_D) -lft 

%.o : %.c 
	$(CC) $(CFLAGS) $(INCH) -c $<

all : $(NAME) $(LIBFT)  
	
$(NAME) : $(SRCS) $(SRCH) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS)  -o $@ 

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
