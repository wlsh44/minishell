NAME = minishell

CC = gcc

INC = -I ./includes/ \
		-I ./libs/libft \

LIBS = -L./libs/libft -lft

CFLAGS = $(INC) #-Wall -Werror -Wextra

SRC =	minishell.c \
		env.c\
 		parsing/parsing.c	\
		error/errors.c 	\
		utils/lstcmd.c 	\
		utils/get_next_line.c \
		execute/execute.c \
		builtins/exit.c \
		builtins/echo.c \
		builtins/pwd.c \

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
