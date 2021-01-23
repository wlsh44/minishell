#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
//extern char **environ;

static size_t	my_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}

static void		my_strcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	s1_len = my_strlen(s1);
	s2_len = my_strlen(s2);
	if (!(arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	my_strcpy(arr, s1, s1_len);
	my_strcpy(arr + s1_len, s2, s2_len);
	arr[s1_len + s2_len] = 0;
	return (arr);
}


char *read_line() {
	char buf[2];
	char *line;
	char *tmp;
	int ret;
	int test;
	buf[0] = ' ';
	buf[1] = '\0';
	line = strdup("");
	while ((test = read(0, buf, 1)) > 0) {
		if (buf[0] == '\0')
			break;
		tmp = strdup(line);
		free(line);
		line = ft_strjoin(tmp, buf);
		free(tmp);
		printf("%c\n", buf[0]);
		//write(1, &buf[0], 1);
		//write(1, "\n", 1);
	}
		//printf("%s\n", line);
//	fflush(stdout);
	return (line);
}

int main(int argc, char *argv[], char *env[]) {

// 	int fd_pipe[2];

// 	int fd;
// 	char buf[] = "arg1";
// 	char buf2[30] = "qqq";
// 		struct stat info;
// 	pid_t pid;

// 	read(-21323, buf, 1);
// 	pipe(fd_pipe);
// 	pid = fork();
// 	if (pid == 0) {
// 		printf("child\n");
// 		dup2(fd_pipe[1], 1); //  1 --> fd_pipe[1]
// 		close(fd_pipe[0]);
// 		close(fd_pipe[1]);
// 		write(1, buf, strlen(buf));
// 		exit(0);
// 	}
// 	//echo 123 | export a=b
// 	while ((wait(NULL)) > 0)
// 		NULL;
// 	pid_t pid2;
// 	printf("\n");
// 	pid2 = fork();
// 	if (pid2 == 0) {
// 		char *line;
// 		dup2(fd_pipe[0], 0);
// 		close(fd_pipe[0]);
// 		close(fd_pipe[1]);
// #include <stdbool.h>
// // 		printf("%d == %llu\n", 0, info.st_ino);
// 		int	option = true ? O_TRUNC : O_APPEND;

// 		fd = open("aaa", O_CREAT | O_WRONLY | option, 0644);
// 		line = read_line();
// 		fflush(stdout);
// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 		close(fd);
// 	}//echo arg1 > aaa 

	int fd1, fd2;
	char buf1[4];
	char buf2[5];
	fd1 = open("234", O_RDONLY);
	dup2(fd1, fd2);
	read(fd1, buf1, 3);
	read(fd2, buf2, 5);
	printf("%s, %s\n", buf1, buf2);
}