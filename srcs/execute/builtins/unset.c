/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:10:48 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 22:47:58 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_unset(t_minishell *ms, char **tmp)
{
	char	*arg;
	int		rt;

	while (**tmp && ft_isspace(**tmp))
		(*tmp)++;
	arg = malloc(sizeof(char) * (ft_strlen(*tmp) + 1));
	if ((rt = get_arg_char_basic(tmp, arg, endline_condition_normal) < 0)
		|| ((rt = check_key(arg)) < 0))
		execute_error(rt);
	else
		delete_env(ms->env, arg);
	free(arg);
}

int		ft_unset(t_minishell *ms, t_node *cur)
{
	char	*tmp;
	int		cnt;

	tmp = cur->arg;
	cnt = count_args(cur->arg);
	while (cnt--)
		init_unset(ms, &tmp);
	return (0);
}
