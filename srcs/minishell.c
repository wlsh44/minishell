#include "minishell.h"

void	sighandler_all(int code)
{
	if (code != SIGQUIT)
		ft_putstr_fd("\nm$ ", STDOUT_FILENO);
}

void	sighandler_quit(int code)
{
	if (code != SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

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
	ms.cmd->tail->type = TAIL;
	ms.cmd->head->type = HEAD;
	ms.env = malloc(sizeof(t_lstenv));
	ms.env->head = malloc(sizeof(t_env_node));
	ms.env->tail = malloc(sizeof(t_env_node));
	ms.env->head->prev = NULL;
	ms.env->head->next = ms.env->tail;
	ms.env->tail->prev = ms.env->head;
	ms.env->tail->next = NULL;

	char	*test;
	char	*line;
	int		ret;

	init_env(&ms, envp);
	ret = 0;

	// ms.fd[0] = -1;
	// ms.fd[1] = -1;
	while (1) {
		ft_putstr_fd("m$ ", STDOUT_FILENO);

		signal(SIGINT, &sighandler_all);
		signal(SIGQUIT, &sighandler_quit);
		ret = get_next_line(0, &line);
		if (ret == -2)
		{
		}
		else if (ret == 0)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(0);
		}
		else if (ret < 0)
		{
			ret = 0;
			continue;
		}
		else
		{
			ms.cmd_line = line;
			ret = parsing(&ms);
			if (ret < 0)
				cmd_error(ret);
			else
			{
				write(1, "parse end\n", 10);
				show(ms.cmd);
				if(!execute(&ms))
					execute_error(ret);
			}
			clear(ms.cmd);
		}
		// free(ms.cmd_line);
		// ms.cmd_line = NULL;

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
