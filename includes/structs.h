#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_node {
	//char *name;
	char *arg;
	int type;
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct {
	t_node *head;
	t_node *tail;
} t_lstcmd;

typedef struct {
	t_lstcmd *cmd;
	char *cmd_line;
	int err;
} t_minishell;

#endif