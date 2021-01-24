#include "minishell.h"

static int read_line(int fd, char **line) {
	char *buf;
	char *tmp;

	buf = ft_strdup("");
	while (read(fd, buf, 1) > 0) {
		if (buf[0] == 0)
			break;
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (0);
}

int ft_redirect_input(t_node *cur) {
	char *line;
	int fd;
	int ret;
	char *tmp;
	char *save;
	char name[5] = "log1";
	
	ret = 0;
	line = ft_strdup("");
	fd = open(cur->arg, O_RDONLY);
	read_line(fd, &line);
	write(1, line, ft_strlen(line));
	close(fd);
	return (ret);
}
