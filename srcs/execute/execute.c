/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:12:02 by schang            #+#    #+#             */
/*   Updated: 2021/01/23 20:59:45 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

bool is_env_cmd(int type) {
	if (type == TYPE_CD || type == TYPE_EXPORT || type == TYPE_UNSET)
		return (true);
	return (false);
}

int execute_command(t_minishell *ms, t_node *cur) {
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
		ret = ft_echo(ms, cur);
	else if (cur->type == TYPE_PWD)
		ret = ft_pwd(cur);
	else if (cur->type == TYPE_REDIRECT_OUTPUT || cur->type == TYPE_DOUBLE_REDIRECT)
		ret = ft_redirect_output(cur);
	else
		ret = ft_bin(ms, cur);
	return (ret);
}

int execute(t_minishell *ms) {
	t_node *cur;
	int ret;

	ret = 1;
	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0)) {
		if (!is_env_cmd(cur->type) && cur->next->type == TYPE_REDIRECT_OUTPUT || cur->next->type == TYPE_REDIRECT_INPUT ||
			cur->next->type == TYPE_DOUBLE_REDIRECT || cur->next->type == TYPE_PIPE ||
			cur->type == TYPE_REDIRECT_OUTPUT ||
			cur->type == TYPE_DOUBLE_REDIRECT || cur->prev->type == TYPE_PIPE) {
			ret = fork_process(ms, cur);
		} else if (cur->type != TYPE_REDIRECT_INPUT || cur->type != TYPE_PIPE)
			ret = execute_command(ms, cur);
		// if(ret < 0)
		// 	break;
		ms->exit_status = ret;
		cur = cur->next;
	}
	ms->fd[0] = -1;
	ms->fd[1] = -1;
	return (0);
}
