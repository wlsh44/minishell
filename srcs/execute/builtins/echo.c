/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:55:13 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 21:34:23 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_minishell *ms, t_node *node)
{
	if (!node->arg)
		return (0);
	ft_putstr_fd(parse_env_val(ms->env, node->arg), 1);
	if (node->type == TYPE_ECHO)
		write(1, "\n", 1);
	return (1);
}
