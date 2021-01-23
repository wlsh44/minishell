#include "minishell.h"

int ft_redirect_input(t_node *cur) {
	char *line;
	int fd;
	int ret;
	int option;
	char buf[2];
	ret = 0;
	
	if (cur->next->type == TYPE_REDIRECT_INPUT) {
		ret = ft_redirect_input(cur->next);
	}
	else {
		line = ft_strdup("");
		fd = open(cur->arg, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (ret);
}
