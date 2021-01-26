#include "minishell.h"

int	exit_status;

void	ft_default_sighandler(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd(" \b\b \b\b \b\n", STDOUT_FILENO);
		ft_putstr_fd("m$ ", STDOUT_FILENO);
		exit_status = 130;
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd(" \b\b \b\b \b", STDOUT_FILENO);
		exit_status = 131;
	}
}

void init_ms(t_minishell *ms)
{
	ms->cmd = malloc(sizeof(t_lstcmd));
	ms->cmd->head = malloc(sizeof(t_node));
	ms->cmd->tail = malloc(sizeof(t_node));
	ms->cmd->head->prev = NULL;
	ms->cmd->head->next = ms->cmd->tail;
	ms->cmd->tail->prev = ms->cmd->head;
	ms->cmd->tail->next = NULL;
	ms->cmd->head->type = HEAD;
	ms->cmd->tail->type = TAIL;
	ms->env = malloc(sizeof(t_lstenv));
	ms->env->head = malloc(sizeof(t_env_node));
	ms->env->tail = malloc(sizeof(t_env_node));
	ms->env->head->prev = NULL;
	ms->env->head->next = ms->env->tail;
	ms->env->tail->prev = ms->env->head;
	ms->env->tail->next = NULL;
	ms->oldfd[0] = -1;
	ms->oldfd[1] = -1;
	ms->newfd[0] = -1;
	ms->newfd[1] = -1;
}

void free_ms(t_minishell *ms)
{
	free(ms->env->head);
	free(ms->env->tail);
	free(ms->env);
	free(ms->cmd->head);
	free(ms->cmd->tail);
	free(ms->cmd);
}

int main(int argc, char *argv[], char *envp[]) {
	t_minishell	ms;
	char		*line;
	int			ret;
	
	(void)argc;
	(void)argv;
	init_ms(&ms);
	init_env(&ms, envp);
	ret = 0;

	while (1) {
		ft_putstr_fd("m$ ", STDOUT_FILENO);

		signal(SIGINT, &ft_default_sighandler);
		signal(SIGQUIT, &ft_default_sighandler);
		ret = get_next_line(0, &line);
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		else if (ret < 0)
			continue;
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
			if (line)
				free(line);
		}
	}
	free_ms(&ms);
	return (exit_status);
}
