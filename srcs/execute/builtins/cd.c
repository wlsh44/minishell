/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:04:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/29 00:51:36 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *ms, t_node *cur)
{
	char	path[PATH_MAX];

	if (cur->next->type == TYPE_REDIRECT_OUTPUT)
	{
		getcwd(path, PATH_MAX);
		ms->oldpath = ft_strdup(path);
	}
	if (ft_strcmp(cur->arg, "") == 0 || ft_strcmp(cur->arg, "~") == 0)
		chdir(get_env_value(ms->env, "HOME"));
	else
	{
		if (chdir(cur->arg) < 0)
		{
			execute_error(NO_DIRECTORY);
			return (ERR_NO_DIRECTORY);
		}
	}
	return (0);
}
