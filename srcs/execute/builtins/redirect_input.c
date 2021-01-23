#include "minishell.h"

int read_line(char **line) {
	char *buf;
	char *tmp;

	buf = ft_strdup("");
	while (read(0, buf, 1) > 0) {
		if (buf[0] == 0)
			break;
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (0);
}

int redirect_input(t_node *cur) {
	char *line;
	int fd;
	int ret;
	int option;

	ret = 0;
	if (cur->prev->type == TYPE_REDIRECT_OUTPUT || cur->prev->type == TYPE_DOUBLE_REDIRECT || cur->next->type == TYPE_REDIRECT_INPUT)
		return (ret);
	line = ft_strdup("");
	fd = open(cur->arg, O_WRONLY);
	read_line(&line);
	write(1, line, ft_strlen(line));
	free(line);
	close(fd);
	return (ret);
}