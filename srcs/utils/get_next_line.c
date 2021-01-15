/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:10:02 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 20:21:10 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	return_line(char **line, char **str_fd, char *nl)
{
	char	*tmp;

	if (nl)
	{
		*line = ft_strndup(*str_fd, (nl - *str_fd));
		tmp = ft_strndup(nl + 1, ft_strlen(nl + 1));
		free(*str_fd);
		*str_fd = tmp;
		return (1);
	}
	if (*str_fd)
	{
		*line = *str_fd;
		*str_fd = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*str[1024];
	char		*nl;
	char		*buf;
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!(nl = ft_strchr(str[fd], '\n'))
		&& (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = 0;
		tmp = str[fd] == NULL ? ft_strndup(buf, ret) :
			ft_strjoin(str[fd], buf);
		if (str[fd])
			free(str[fd]);
		str[fd] = tmp;
	}
	free(buf);
	if (ret < 0)
		return (-1);
	return (return_line(line, &str[fd], nl));
}
