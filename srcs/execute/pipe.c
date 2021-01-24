#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void set_pipe(t_minishell *ms, t_node *cur) {
	if (cur->type == TYPE_REDIRECT_OUTPUT || cur->type == TYPE_DOUBLE_REDIRECT ||
		cur->prev->type == TYPE_PIPE || cur->prev->type == TYPE_REDIRECT_INPUT)
	{
		printf("dup %d 0\n", ms->oldfd[0]);		
		dup2(ms->oldfd[0], STDIN_FILENO);
		close(ms->oldfd[0]);
		close(ms->oldfd[1]);
	}
	if (cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_DOUBLE_REDIRECT ||
		cur->next->type == TYPE_PIPE || cur->type == TYPE_REDIRECT_INPUT) {
		printf("dup %d 1\n", ms->newfd[1]);		
		dup2(ms->newfd[1], STDOUT_FILENO);
		close(ms->newfd[0]);
		close(ms->newfd[1]);
		//ms->io_flag[1] = true;
	}
	// close(ms->fd[0]);
	// close(ms->fd[1]);
}

void sort_cmd(t_node *cur) {
	t_node *node;

	while (cur->next->type == TYPE_REDIRECT_INPUT) {
		node = cur->next;
		node->next->prev = cur;
		cur->prev->next = node;
		node->prev = cur->prev;
		cur->prev = node;
		cur->next = node->next;
		node->next = cur;
	}
}

void close_fd(t_minishell *ms, t_node *cur) {
	if (cur->type == TYPE_REDIRECT_OUTPUT || cur->type == TYPE_DOUBLE_REDIRECT ||
		cur->prev->type == TYPE_PIPE || cur->prev->type == TYPE_REDIRECT_INPUT) {
		close(ms->oldfd[0]);
printf("close %d 0\n", ms->oldfd[0]);
	}
	if (cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_DOUBLE_REDIRECT ||
		cur->next->type == TYPE_PIPE || cur->type == TYPE_REDIRECT_INPUT) {
		close(ms->newfd[1]);
printf("close %d 1\n", ms->newfd[1]);
	}
}

void save_pipe(int old[], int new[]) {
	old[0] = new[0];
	old[1] = new[1];
}

int fork_process(t_minishell *ms, t_node *cur) {
	pid_t pid;
	int io_flag;
	int ret;
	int status;
	int c = 0;

	// io_flag = STDIN_FILENO;
	if (cur->next->type == TYPE_REDIRECT_INPUT) {
		sort_cmd(cur);
		show(ms->cmd);
		ret = fork_process(ms, cur->prev);
	}
	printf("type: %d\n", cur->type);
	save_pipe(ms->oldfd, ms->newfd);
	if ((cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_DOUBLE_REDIRECT || cur->type == TYPE_REDIRECT_INPUT || cur->next->type == TYPE_PIPE || cur->prev->type == TYPE_PIPE)) {
		if (pipe(ms->newfd) < 0)
			printf("error\n");
		//io_flag = STDOUT_FILENO;
	}
	printf("old pipe: %d %d\n", ms->oldfd[0], ms->oldfd[1]);
	printf("new pipe: %d %d\n", ms->newfd[0], ms->newfd[1]);
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0) {
		set_pipe(ms, cur);//앞이 red면 0, 뒤가 red면 1 둘 다 해줘야 함, 안한건 부모에서 꼭 닫기!!
		ret = execute_command(ms, cur);
		exit(0);
	}
	close_fd(ms, cur);
	return (ret);
}
//echo 123 > why