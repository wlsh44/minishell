/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:04:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 18:24:55 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *ms, t_node *cur)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	update_env(ms->env, ft_strdup("OLDPWD"), ft_strdup(path));
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
	getcwd(path, PATH_MAX);
	update_env(ms->env, ft_strdup("PWD"), ft_strdup(path));
	return (0);
}
