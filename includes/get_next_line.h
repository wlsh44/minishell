
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define FD_MAX 1024

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include "libft.h"

int		get_next_line(int fd, char **line);

#endif
