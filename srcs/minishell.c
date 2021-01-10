#include "minishell.h"

int main(int argc, char *argv[], char *envp[]) {
	t_minishell ms;

	// for (int i = 0; i < 20; i++)
	// 	buf[i] = 0;
	char *l1 = "cd test";
	char *l2 = "cd";
	char *l3 = "cd  test";
	char *l4 = "  cd  test";
	char *l5 = "cd test   ";
	char *l6 = "cd \"test\"";
	char *l7 = "cd atg atg";
	char *l8 = "pwd";
	char *l9 = "pwd \'\'";
	char *l10 = "cd \\\"test\\\"";
	char *l11 = "cd a\'a";
	ms.cmd = malloc(sizeof(ms.cmd));
	ms.cmd->head = malloc(sizeof(t_node));
	ms.cmd->tail = malloc(sizeof(t_node));
	ms.cmd->head->prev = NULL;
	ms.cmd->head->next = ms.cmd->tail;
	ms.cmd->tail->prev = ms.cmd->head;
	ms.cmd->tail->next = NULL;
	ms.env = malloc(sizeof(t_lstenv));
	ms.env->head = malloc(sizeof(t_env_node));
	char *test;


	char buf[1000];

	init_env(ms, envp);
	while (1) {
		for (int i = 0; i < 1000; i++)
			buf[i] = 0;
		read(STDIN_FILENO, buf, 1000);
		ms.cmd_line = buf;
		int ret;
		if ((ret = parsing(&ms)) < 0)
			cmd_error(ret);
		else
			show(ms.cmd);
		clear(ms.cmd);
	}
// //	ms.cmd_line = l2;
// 	int ret;
// 	// if ((ret = parsing(&ms)) < 0)
// 	// 	cmd_error(ret);
// 	// show(ms.cmd);
// 	// clear(ms.cmd);
	// ms.cmd_line = "export   \"asdf\"=a  ";
	// int ret;
	// if ((ret = parsing(&ms)) < 0)
	// 	cmd_error(ret);
	// else
	// 	show(ms.cmd);
	// clear(ms.cmd);
}