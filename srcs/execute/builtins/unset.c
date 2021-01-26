/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:10:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 22:53:04 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_minishell *ms, t_node *cur)
{
	char	*ptr;
	char	**args;
	char	**tmp;
	char	*name;
	char	*val;

	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args && !(val = NULL))
	{
		ptr = ft_strchr(*args, '=');
		if (ptr != NULL)
			return (NOT_VAILD_IDENTIFIER);
		else
		{
			if ((name = parse_env_val(ms, *args)) == NULL)
				continue;
			delete_env(ms->env, name);
			free(name);
			break ;
		}
		args++;
	}
	while (*tmp) {
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	return (0);
}
