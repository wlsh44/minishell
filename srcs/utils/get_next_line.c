
#include "get_next_line.h"

static void	handle_line(char **str, char **buffer)
{
	char	*temp;

	if (*str == NULL)
		temp = ft_strdup(*buffer);
	else
		temp = ft_strjoin(*str, *buffer);
	if (*str != NULL)
		free(*str);
	*str = temp;
}

static int	get_line(char **save, char **line, char *end_line)
{
	char	*temp;

	if (end_line != NULL)
	{
		temp = *save;
		*line = ft_substr(*save, 0, end_line - *save);
		*save = ft_strdup(end_line + 1);
		free(temp);
		return (1);
	}
	else if (*save != NULL)
	{
		*line = *save;
		*save = NULL;
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*save[FD_MAX];
	char		*buffer;
	char		*end_line;
	int			size;

	size = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!(end_line = ft_strchr(save[fd], '\n')) && size != 0)
	{
		if ((size = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[size] = '\0';
		handle_line(&save[fd], &buffer);
	}
	free(buffer);
	return (get_line(&save[fd], line, end_line));
}
