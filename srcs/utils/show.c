/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:03:11 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:03:30 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	show(t_lstcmd *cmd)
{
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail)
	{
		write(1, "TYPE: ", 6);
		write(1, ft_itoa(cur->type), 2);
		if (cur->name)
		{
			write(1, "\nNAME: ", 8);
			write(1, cur->name, ft_strlen(cur->name));
		}
		write(1, "\nARG: ", 6);
		if (cur->arg)
			write(1, cur->arg, ft_strlen(cur->arg));
		write(1, "\n==========\n", 12);
		cur = cur->next;
	}
}
