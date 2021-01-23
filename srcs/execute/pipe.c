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
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0) {
		if (cur->next->type == TYPE_REDIRECT_INPUT) {
			ft_redirect_input(cur->next);
		}
		else
			set_pipe(ms->fd, io_flag);
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