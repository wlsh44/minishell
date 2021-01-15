/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:44:07 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 20:26:59 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	free_lstcmd(t_lstcmd *cmd)
{
	clear(cmd);
}

void	free_lstenv(t_lstenv *env)
{
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail) {
		cur = cur->next;
		if (cur->prev->name) {
			free(cur->prev->name);
			cur->prev->name = NULL;
		}
		if (cur->prev->val)
		{
			free(cur->prev->val);
			cur->prev->name = NULL;
		}
		free(cur->prev);
		cur->prev = NULL;
	}
	env->head->next = env->tail;
	env->tail->prev = env->head;
}

void	ft_exit(t_minishell *ms)
{
	free_lstcmd(ms->cmd);
	free_lstenv(ms->env);
	free(ms->cmd);
	free(ms->env);

	/*
	if (ms->cmd_line)
	{
		free(ms->cmd_line);
		ms->cmd_line = NULL;
	}
	*/

	ms->cmd = NULL;
	ms->env = NULL;

	write(1, "exit\n", 5);
	exit(0);
}
