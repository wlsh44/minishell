#include "minishell.h"


void push_back(t_lstcmd *cmd, int type, char *arg) {
	t_node *node;

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
	t_node *node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->name = name;
	node->arg = arg;
	node->prev = cmd->tail->prev;
	node->next = cmd->tail;
	cmd->tail->prev->next = node;
	cmd->tail->prev = node;
}

t_node *pop(t_lstcmd *cmd) {
	return (cmd->head->next);
}

void delete_cmd(t_node *cur) {
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

void clear(t_lstcmd *cmd) {
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail) {
		cur = cur->next;
		if (cur->prev->arg) {
			free(cur->prev->arg);
			cur->prev->arg = NULL;
		}
		free(cur->prev);
		cur->prev = NULL;
	}
	cmd->head->next = cmd->tail;
	cmd->tail->prev = cmd->head;
}


#include <string.h>
void show(t_lstcmd *cmd) {
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail) {
		//printf("TYPE: %d\nARG: %s\n", cur->type, cur->arg);
		write(1, "TYPE: ", 6);
		write(1, ft_itoa(cur->type), 2);
		if (cur->name)
		{
			write(1, "\nNAME: ", 8);
			write(1, cur->name, ft_strlen(cur->name));
		}
		write(1, "\nARG: ", 6);
		if (cur->arg) {
			write(1, "|", 1);
			write(1, cur->arg, ft_strlen(cur->arg));
			write(1, "|", 1);
		}
		write(1, "\n==========\n", 12);
		cur = cur->next;
	}
}
















