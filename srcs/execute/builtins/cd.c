/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:04:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:47:44 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *ms, t_node *cur)
{
	if (ft_strcmp(cur->arg, "") == 0)
	{
		chdir(get_env_value(ms->env, "HOME"));
	}
	else
	{
		if (chdir(cur->arg) < 0)
			return (NO_DIRECTORY);
	}
	return (0);
}
