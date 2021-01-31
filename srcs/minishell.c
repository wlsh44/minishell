/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:45:36 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 22:31:58 by schang           ###   ########.fr       */
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

int		check_syntax(char *line)
{
	int	i;
	int	flag;

	i = 0;
	while (line[i])
	{
		flag = false;
		while (line[i] && line[i] != ';')
		{
			if (!ft_isspace(line[i]))
				flag = true;
			i++;
		}
		if (!flag)
			return (-1);
		if (line[i] == 0)
			break ;
		i++;
	}
	return (0);
}

void	minishell(t_minishell *ms, char *line)
{
	char	*cmd;
	int		i;
	int		ret;

	if ((ret = check_syntax(line)) < 0)
	{
		cmd_error(SYNTAX_ERROR);
		return ;
	}
	i = 0;
	while (line[i])
	{
		i = sub_cmd(line, &cmd, i);
		ret = parsing(ms, cmd);
		if (ret < 0)
			cmd_error(ret);
		else
			execute(ms);
		clear(ms->cmd);
		free(cmd);
	}
	free_and_null(line);
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
	while (!(ret = 0))
	{
		ft_putstr_fd("minishell$ ", STDOUT_FILENO);
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
			minishell(&ms, line);
	}
	return (g_exit_status);
}
