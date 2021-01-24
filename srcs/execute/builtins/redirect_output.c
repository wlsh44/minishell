#include "minishell.h"

int read_line(int fd, char **line) {
	char *buf;
	char *tmp;

	buf = ft_strdup("");
	while (read(fd, buf, 1) > 0) {
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (0);
}

int ft_redirect_output(t_node *cur) {
	char *line;
	int fd;
	int ret;
	int option;

	ret = 0;
	line = ft_strdup("");
	option = cur->type == TYPE_REDIRECT_OUTPUT ? O_TRUNC : O_APPEND;
	fd = open(cur->arg, O_CREAT | O_WRONLY | option, 0644);
	read_line(STDIN_FILENO, &line);
	if ((cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_DOUBLE_REDIRECT || cur->prev->type == HEAD))
		write(1, line, ft_strlen(line));
	else 
		write(fd, line, ft_strlen(line));
	free(line);
	close(fd);
	return (ret);
}
