NAME = minishell

CC = gcc

INC = ./includes/minishell \
	./includes/structs \
	./includes/parsing

CFLAGS = -Wall -Werror -Wextra

SRC = parsing.c	\
		minishell.c \

DIR_SRCS = ./srcs/
HEADER = ./includes/

SRCS = $(addprefix $(SRC_DIR), $(SRC))


#OBJS = $(SRCS:.c=.o)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) -I $(HEADER) $(OBJS) -o $(NAME)

$(OBJS)%.o: $(DIR_SRCS)%.c
				@$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

$(DIR_OBJS):
				@mkdir $(DIR_OBJS)
				@mkdir $(DIR_OBJS)$(DIR_COMMANDS)
				@mkdir $(DIR_OBJS)$(DIR_CMDS_RUN)
				@mkdir $(DIR_OBJS)$(DIR_ENV_V)
				@mkdir $(DIR_OBJS)$(DIR_ERRORS)
				@mkdir $(DIR_OBJS)$(DIR_PARSING)
				@mkdir $(DIR_OBJS)$(DIR_STYLE)
				@mkdir $(DIR_OBJS)$(DIR_UTILS)

RM			=	rm -rf


all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re libft