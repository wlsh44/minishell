/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:05:34 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:48:50 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *ms)
{
	t_env_node	*cur;

	cur = ms->env->head->next;
	while (cur != ms->env->tail)
	{
		if (cur->val)
		{
			write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
			write(STDOUT_FILENO, "\n", 1);
		}
		cur = cur->next;
	}
	return (0);
}
