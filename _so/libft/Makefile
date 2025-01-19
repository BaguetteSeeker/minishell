# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaret <souaret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 12:06:38 by souaret           #+#    #+#              #
#    Updated: 2024/11/24 23:41:20 by souaret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS= -Wall -Wextra -Werror -g3 -I./$(INCL)

SRC =	ft_atoi.c ft_isalpha.c ft_isalnum.c	 ft_isascii.c	ft_isdigit.c 	\
		ft_isprint.c ft_tolower.c ft_toupper.c ft_tolower.c ft_strncmp.c 	\
		ft_strlen.c ft_strchr.c ft_strnstr.c ft_strlcpy.c ft_memset.c	 	\
		ft_bzero.c ft_memchr.c ft_strlcat.c ft_strrchr.c ft_memcpy.c	 	\
		ft_memcmp.c ft_memmove.c ft_calloc.c ft_strdup.c ft_substr.c	 	\
		ft_strjoin.c ft_strtrim.c ft_strlower.c 	ft_strupper.c 			\
		ft_split.c 	ft_itoa.c 	ft_strmapi.c 	ft_striteri.c 	ft_strcmp.c	\
		ft_putstr.c 	ft_isnumeric.c 	ft_putchar_fd.c 	ft_putstr_fd.c 	\
		ft_putendl_fd.c 	ft_putnbr_fd.c 	ft_abs.c 	ft_itoh.c			\
		ft_atof.c

OBJ := $(SRC:.c=.o)
INC	=	libft.h

SRC_B=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c		\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c	\
		ft_lstmap.c

OBJ_B:= $(SRC_B:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC) $(OBJ) $(INC)
	ar -rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

bonus:	$(OBJ) $(OBJ_B)
	ar -rcs $(NAME) $(OBJ) $(OBJ_B)

norm:
	norminette $(SRC) | more
	norminette $(INC) | more

normb:
	norminette $(SRC_B) | more

	
test:	$(NAME) $(OBJ) $(INC)
	$(CC) $(CFLAGS) ../Libft-main.c libft.a -o libft_test
	./libft_test
#	@rm -f libft_test

testv:	$(NAME) $(OBJ) $(INC)
	$(CC) $(CFLAGS) ../Libft-main.c libft.a -o libft_test
	valgrind -s --track-origins=yes ./libft_test
#	@rm -f libft_test

retest:
	rm -f libft_test

print_obj:
	@echo $(OBJ)

#.PHONY: re fclean clean all


#temp:
#		
#		ft_lstadd_back.c ft_lstclear.c 					 
#		ft_lstiter.c ft_lstmap.c 
