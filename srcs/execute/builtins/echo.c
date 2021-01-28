/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:55:13 by schang            #+#    #+#             */
/*   Updated: 2021/01/23 21:00:51 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_minishell *ms, t_node *node)
{
	char	*val;

	if (!node->arg)
		return (0);
	write(1, node->arg, ft_strlen(node->arg));
	if (node->type == TYPE_ECHO)
		write(1, "\n", 1);
	return (0);
}
