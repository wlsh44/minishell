/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:55:13 by schang            #+#    #+#             */
/*   Updated: 2021/01/17 21:02:29 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_minishell *ms, t_node *node)
{
	char	*val;

	if (!node->arg)
		return (0);
	if ((val = parse_env_val(ms->env, node->arg)))
		ft_putstr_fd(val, 1);
	if (node->type == TYPE_ECHO)
		write(1, "\n", 1);
	return (1);
}
