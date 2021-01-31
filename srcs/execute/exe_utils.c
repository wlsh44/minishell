#include "minishell.h"

void	swap_cmd(t_node *cur)
{
	t_node	*node;

	node = cur->next;
	node->next->prev = cur;
	cur->prev->next = node;
	node->prev = cur->prev;
	cur->prev = node;
	cur->next = node->next;
	node->next = cur;
}

void	concat_node(t_node *cur, t_node *node)
{
	char	*tmp;

	if (ft_strcmp(cur->arg, "") == 0)
	{
		free(cur->arg);
		cur->arg = ft_strdup(node->name);
	}
	else
	{
		tmp = cur->arg;
		cur->arg = ft_strjoin(cur->arg, " ");
		free(tmp);
		tmp = cur->arg;
		cur->arg = ft_strjoin(cur->arg, node->name);
		free(tmp);
	}
	if (ft_strcmp(node->arg, ""))
	{
		tmp = cur->arg;
		cur->arg = ft_strjoin(cur->arg, " ");
		free(tmp);
		tmp = cur->arg;
		cur->arg = ft_strjoin(cur->arg, node->arg);
		free(tmp);
	}
}

void	change_cmd_to_arg(t_lstcmd *cmd)
{
	t_node	*cur;
	t_node	*node;
	t_node	*tmp;

	cur = cmd->head->next;
	while (cur != cmd->tail)
	{
		if (cur->type / 10 == 1)
		{
			node = cur->next;
			while (node != cmd->tail && node->type / 10 == 1)
			{
				concat_node(cur, node);
				tmp = node;
				node = node->next;
				delete_cmd(tmp);
			}
			cur = node;
		}
		else
			cur = cur->next;
	}
}

void	sort_cmd(t_lstcmd *cmd)
{
	t_node	*cur;
	bool	changed;

	while (1)
	{
		changed = false;
		cur = cmd->head->next;
		while (cur->next != cmd->tail)
		{
			if (cur->type == TYPE_PIPE || cur->next->type == TYPE_PIPE)
				cur = cur->next;
			else if (cur->type / 10 > cur->next->type / 10)
			{
				swap_cmd(cur);
				changed = true;
			}
			else
				cur = cur->next;
		}
		if (!changed)
			break;
	}
	change_cmd_to_arg(cmd);
}