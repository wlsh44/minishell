/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:52:28 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 23:53:44 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_minishell *ms, t_node *cur)
{
	if (ms->newfd[0] == -1 && ms->newfd[1] == -1)
		return ;
	if (cur->type == TYPE_REDIRECT_OUTPUT
		|| cur->type == TYPE_DOUBLE_REDIRECT || cur->prev->type == TYPE_PIPE
		|| cur->prev->type == TYPE_REDIRECT_INPUT)
	{
		dup2(ms->oldfd[0], STDIN_FILENO);
		close(ms->oldfd[0]);
		close(ms->oldfd[1]);
	}
	if (cur->next->type == TYPE_REDIRECT_OUTPUT
		|| cur->next->type == TYPE_PIPE
		|| cur->next->type == TYPE_DOUBLE_REDIRECT
		|| cur->type == TYPE_REDIRECT_INPUT)
	{
		dup2(ms->newfd[1], STDOUT_FILENO);
		close(ms->newfd[0]);
		close(ms->newfd[1]);
	}
}

void	sort_cmd(t_node *cur)
{
	t_node	*node;

	while (cur->next->type == TYPE_REDIRECT_INPUT)
	{
		node = cur->next;
		node->next->prev = cur;
		cur->prev->next = node;
		node->prev = cur->prev;
		cur->prev = node;
		cur->next = node->next;
		node->next = cur;
	}
}

void	close_used_fd(t_minishell *ms, t_node *cur)
{
	if (ms->newfd[0] == -1 && ms->newfd[1] == -1)
		return ;
	if (cur->type == TYPE_REDIRECT_OUTPUT || cur->type == TYPE_DOUBLE_REDIRECT
		|| cur->prev->type == TYPE_PIPE
		|| cur->prev->type == TYPE_REDIRECT_INPUT)
	{
		close(ms->oldfd[0]);
		ms->oldfd[0] = -1;
	}
	if (cur->next->type == TYPE_REDIRECT_OUTPUT
		|| cur->next->type == TYPE_DOUBLE_REDIRECT
		|| cur->next->type == TYPE_PIPE || cur->type == TYPE_REDIRECT_INPUT)
	{
		close(ms->newfd[1]);
		ms->newfd[1] = -1;
	}
}

void	save_pipe(int old[], int new[])
{
	old[0] = new[0];
	old[1] = new[1];
}

int		fork_process(t_minishell *ms, t_node *cur)
{
	pid_t	pid;
	int		ret;
	int		status;

	if (cur->next->type == TYPE_REDIRECT_INPUT)
	{
		sort_cmd(cur);
		ret = fork_process(ms, cur->prev);
	}
	save_pipe(ms->oldfd, ms->newfd);
	if ((cur->next->type == TYPE_REDIRECT_OUTPUT
		|| cur->next->type == TYPE_DOUBLE_REDIRECT
		|| cur->type == TYPE_REDIRECT_INPUT
		|| cur->next->type == TYPE_PIPE || cur->prev->type == TYPE_PIPE))
		pipe(ms->newfd);
	if ((pid = fork()) > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		set_pipe(ms, cur);
		status = execute_command(ms, cur);
		exit(status);
	}
	close_used_fd(ms, cur);
	status = WEXITSTATUS(status);
	return (status);
}
