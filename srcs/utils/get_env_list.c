/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:52:10 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 22:55:11 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_list(t_minishell *ms)
{
	int			cnt;
	char		*tmp;
	char		**env_list;
	t_env_node	*cur;

	cnt = 0;
	cur = ms->env->head->next;
	while (cur != ms->env->tail)
	{
		cur = cur->next;
		cnt++;
	}
	if (!(env_list = ft_calloc(sizeof(char *), (cnt + 1))))
		return (NULL);
	cur = ms->env->head->next;
	cnt = 0;
	while (cur != ms->env->tail)
	{
		tmp = ft_strjoin(cur->name, "=");
		env_list[cnt] = ft_strjoin(tmp, cur->val);
		free(tmp);
		cur = cur->next;
		cnt++;
	}
	return (env_list);
}
