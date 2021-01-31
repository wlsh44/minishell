# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 21:40:59 by schang            #+#    #+#              #
#    Updated: 2021/01/31 18:16:06 by schang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INC = -I ./includes/ \
		-I ./libs/libft \

LIBS = -L./libs/libft -lft

CFLAGS = $(INC) -Wall -Werror -Wextra

SRC =	minishell.c \
		signal.c \
		env/env.c \
		env/env_utils.c \
 		parsing/parsing.c	\
 		parsing/parsing_cd.c	\
 		parsing/parsing_pwd.c	\
 		parsing/parsing_env.c	\
 		parsing/parsing_echo.c	\
 		parsing/parsing_export.c	\
 		parsing/parsing_unset.c	\
 		parsing/parsing_exit.c	\
 		parsing/parsing_sep.c	\
 		parsing/parsing_utils.c	\
 		parsing/parsing_utils2.c	\
 		parsing/parsing_bin.c	\
		error/errors.c 	\
		utils/lstcmd.c 	\
		utils/get_next_line.c \
		utils/free_double_char.c \
		utils/get_env_list.c \
		utils/ft_bin_args.c \
		utils/show.c \
		utils/endline_condition_quote.c \
		utils/get_command.c \
		utils/ft_check_file.c \
		utils/ft_check_command.c \
		utils/ft_split_path.c \
		utils/ft_check_permission.c \
		utils/ft_free_and_null.c \
		execute/execute.c \
		execute/execute_bin.c \
		execute/exe_utils.c \
		execute/bin.c \
		execute/pipe.c \
		execute/builtins/exit.c \
		execute/builtins/echo.c \
		execute/builtins/pwd.c \
		execute/builtins/cd.c \
		execute/builtins/env.c \
		execute/builtins/unset.c \
		execute/builtins/export.c \
		execute/builtins/redirect.c \


DIR_SRCS = ./srcs/

SRCS = $(addprefix $(DIR_SRCS), $(SRC))

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C libs/libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

RM			=	rm -rf

all: $(NAME)

clean:
	$(MAKE) clean -C libs/libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libs/libft
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re libft
