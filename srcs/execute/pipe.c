#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
void set_pipe(int fd[2], int io) {
	dup2(fd[io], io);
	close(fd[0]);
	close(fd[1]);
}

int fork_process(t_minishell *ms, t_node *cur) {
	pid_t pid;
	int io_flag;
	int ret;
	int status;
	int c = 0;

	io_flag = STDIN_FILENO;
	if ((cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_DOUBLE_REDIRECT) && ms->fd[0] == -1) {
		if (pipe(ms->fd) < 0)
			printf("error\n");
		io_flag = STDOUT_FILENO;
	}
	if (cur->next->type == TYPE_REDIRECT_INPUT && ms->fd[0] != -1) {
		pipe(ms->fd);
	}
	if (cur->type == TYPE_REDIRECT_INPUT)
		io_flag = STDOUT_FILENO;
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0) {
		set_pipe(ms->fd, io_flag);
		if (cur->next->type == TYPE_REDIRECT_INPUT)
			fork_process(ms, cur->next);
		ret = execute_command(ms, cur);
		write(1, &c, 1);
		exit(0);
	}
	return (0);
}
/*
0 -> 3
1 
2
3 -> close
4
5
6
*/