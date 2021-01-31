/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:10:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 18:49:03 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_error(bool *flag, char *arg)
{
	if (ft_strchr(arg, NOT_VAILD_IDENTIFIER))
	{
		if (!*flag)
		{
			*flag = true;
			execute_error(NOT_VAILD_IDENTIFIER);
		}
		return (true);
	}
	if (ft_strchr(arg, WRONG_QUOTE))
	{
		if (!*flag)
		{
			*flag = true;
			execute_error(WRONG_QUOTE);
		}
		return (true);
	}
	return (false);
}

int			ft_unset(t_minishell *ms, t_node *cur)
{
	char	**args;
	char	**tmp;
	bool	flag;

	flag = false;
	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args)
	{
		if (!is_error(&flag, *args))
		{
			if (get_env_value(ms->env, *args) != NULL)
				delete_env(ms->env, *args);
		}
		args++;
	}
	free_double_char(tmp);
	return (0);
}
