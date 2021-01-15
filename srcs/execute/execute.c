/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:12:02 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 21:12:03 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_minishell *ms) {
	t_node *cur;
	int ret;

	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0)) {
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
			ret = ft_pwd(cur);
		cur = cur->next;
	}
	return (0);
}
