/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:04:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 20:39:45 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *ms, t_node *cur) {
	char path[PATH_MAX];

	if (cur->next->type == TYPE_PIPE)
		return (0);
	if (cur->next->type == TYPE_REDIRECT_OUTPUT) {
		getcwd(path, PATH_MAX);
		ms->oldpath = ft_strdup(path);
	}
	if (ft_strcmp(cur->arg, "") == 0) {
		chdir(get_env_value(ms->env, "HOME"));
	}
	else
	{
		if (chdir(cur->arg) < 0)
			return (NO_DIRECTORY);
	}
	return (0);
}
