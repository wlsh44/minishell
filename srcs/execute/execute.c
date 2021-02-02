/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:12:02 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 23:07:30 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_command(t_minishell *ms, t_node *cur)
{
	int ret;

	if (cur->type == TYPE_CD)
		ret = ft_cd(ms, cur);
	else if (cur->type == TYPE_ENV)
		ret = ft_env(ms);
	else if (cur->type == TYPE_EXPORT)
		ret = ft_export(ms, cur);
	else if (cur->type == TYPE_UNSET)
		ret = ft_unset(ms, cur);
	else if (cur->type == TYPE_EXIT)
		ret = ft_exit(ms);
	else if (cur->type == TYPE_ECHO || cur->type == TYPE_ECHO_N)
		ret = ft_echo(cur);
	else if (cur->type == TYPE_PWD)
		ret = ft_pwd();
	else if (cur->type == TYPE_REDIRECT_OUTPUT
		|| cur->type == TYPE_DOUBLE_REDIRECT)
		ret = ft_redirect_output(ms, cur);
	else if (cur->type == TYPE_REDIRECT_INPUT)
		ret = ft_redirect_input(cur);
	else
		ret = ft_bin(ms, cur);
	return (ret);
}

void	close_fd(t_minishell *ms)
{
	if (ms->newfd[0] != -1)
	{
		close(ms->newfd[0]);
		ms->newfd[0] = -1;
	}
	if (ms->newfd[1] != -1)
	{
		close(ms->newfd[1]);
		ms->newfd[1] = -1;
	}
	if (ms->oldfd[0] != -1)
	{
		close(ms->oldfd[0]);
		ms->oldfd[0] = -1;
	}
	if (ms->oldfd[1] != -1)
	{
		close(ms->oldfd[1]);
		ms->oldfd[1] = -1;
	}
}

bool	is_fork_type(t_node *cur)
{
	if (cur->next->type == TYPE_REDIRECT_OUTPUT
		|| cur->next->type == TYPE_REDIRECT_INPUT
		|| cur->next->type == TYPE_DOUBLE_REDIRECT
		|| cur->next->type == TYPE_PIPE
		|| cur->type == TYPE_REDIRECT_OUTPUT
		|| cur->type == TYPE_REDIRECT_INPUT
		|| cur->type == TYPE_DOUBLE_REDIRECT
		|| cur->prev->type == TYPE_PIPE
		|| cur->prev->type == TYPE_REDIRECT_INPUT)
		return (true);
	return (false);
}

int		execute(t_minishell *ms)
{
	t_node	*cur;
	int		ret;
	char	*tmp;

	sort_cmd(ms->cmd);
	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0))
	{
		if (is_fork_type(cur))
			ret = fork_process(ms, cur);
		else if (!(cur->type == TYPE_REDIRECT_INPUT || cur->type == TYPE_PIPE))
		{
			if (cur->arg)
			{
				tmp = cur->arg;
				cur->arg = parsing_env_val(ms->env, cur->arg);
				free(tmp);
			}
			ret = execute_command(ms, cur);
		}
		cur = cur->next;
	}
	close_fd(ms);
	return (ret);
}
