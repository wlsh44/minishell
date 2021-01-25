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

void init_ms(t_minishell *ms)
{
	ms->cmd = malloc(sizeof(ms->cmd));
	ms->cmd->head = malloc(sizeof(t_node));
	ms->cmd->tail = malloc(sizeof(t_node));
	ms->cmd->head->prev = NULL;
	ms->cmd->head->next = ms->cmd->tail;
	ms->cmd->tail->prev = ms->cmd->head;
	ms->cmd->tail->next = NULL;
	ms->env = malloc(sizeof(t_lstenv));
	ms->env->head = malloc(sizeof(t_env_node));
	ms->env->tail = malloc(sizeof(t_env_node));
	ms->env->head->prev = NULL;
	ms->env->head->next = ms->env->tail;
	ms->env->tail->prev = ms->env->head;
	ms->env->tail->next = NULL;
}

int main(int argc, char *argv[], char *envp[]) {
	t_minishell ms;
	char	*line;
	int		ret;

	init_ms(&ms);
	init_env(&ms, envp);
	ret = 0;

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
				show(ms.cmd);
				if(!execute(&ms))
					execute_error(ret);
			}
			clear(ms.cmd);
		}
		// free(ms.cmd_line);
		// ms.cmd_line = NULL;

	}
}
