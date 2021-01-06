# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 20:49:18 by schang            #+#    #+#              #
#    Updated: 2021/01/06 21:15:45 by schang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INC = -I./libs/libft \
	-I./libs/get_next_line \

LIBS = -L./libs/libft -lft

CFLAGS = $(INC) -Wall -Werror -Wextra

SRCS = libs/get_next_line/get_next_line.c	\
		libs/get_next_line/get_next_line_utils.c	\
		srcs/minishell.c \

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C libs/libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re libft
