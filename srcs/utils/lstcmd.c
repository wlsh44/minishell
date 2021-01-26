/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:55:57 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:03:39 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_back(t_lstcmd *cmd, int type, char *arg)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->name = NULL;
	node->arg = arg;
	node->prev = cmd->tail->prev;
	node->next = cmd->tail;
	cmd->tail->prev->next = node;
	cmd->tail->prev = node;
}

void	push_back_normal(t_lstcmd *cmd, int type, char *name, char *arg)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->name = name;
	node->arg = arg;
	node->prev = cmd->tail->prev;
	node->next = cmd->tail;
	cmd->tail->prev->next = node;
	cmd->tail->prev = node;
}

t_node	*pop(t_lstcmd *cmd)
{
	return (cmd->head->next);
}

void	delete_cmd(t_node *cur)
{
	if (cur->name)
	{
		free(cur->name);
		cur->name = NULL;
	}
	if (cur->arg)
	{
		free(cur->arg);
		cur->arg = NULL;
	}
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur);
}

void	clear(t_lstcmd *cmd)
{
	t_node	*cur;

	cur = cmd->head->next;
	while (cur != cmd->tail)
	{
		cur = cur->next;
		if (cur->prev->arg)
		{
			free(cur->prev->arg);
			cur->prev->arg = NULL;
		}
		free(cur->prev);
		cur->prev = NULL;
	}
	cmd->head->next = cmd->tail;
	cmd->tail->prev = cmd->head;
}
