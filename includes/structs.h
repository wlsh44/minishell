#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_env_node {
	char *name;
	char *val;
	struct s_env_node *next;
	struct s_env_node *prev;
} t_env_node;

typedef struct {
	t_env_node *head;
	t_env_node *tail;
} t_lstenv;

typedef struct s_node {
	char *name;
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
	t_lstenv *env;
	int oldfd[2];
	int newfd[2];
	bool io_flag[0];
	// char *buf;
	//int last_cmd;
	int exit_status;
	char *cmd_line;
	int err;
} t_minishell;

typedef struct	s_signal
{
	int	sig_int;
	int	sig_quit;
}				t_signal;

#endif
