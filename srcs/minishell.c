/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:45:36 by schang            #+#    #+#             */
/*   Updated: 2021/01/28 22:07:00 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

void	init_ms(t_minishell *ms)
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

int		main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;
	char		*line;
	int			ret;

	(void)argc;
	(void)argv;
	init_ms(&ms);
	init_env(&ms, envp);
	ret = 0;
	while (1)
	{
		ft_putstr_fd("m$ ", STDOUT_FILENO);
		signal(SIGINT, &default_sighandler);
		signal(SIGQUIT, &default_sighandler);
		ret = get_next_line(0, &line);
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		else if (ret < 0)
			continue ;
		else
		{
			ms.cmd_line = line;
			ret = parsing(&ms);
			if (ret < 0)
				cmd_error(ret);
			else
			{
				show(ms.cmd);
				if (!(g_exit_status = execute(&ms)))
					execute_error(ret);
			}
			clear(ms.cmd);
			if (line)
				free(line);
		}
	}
	return (g_exit_status);
}
