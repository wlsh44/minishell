#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

void push_back(t_lstcmd *cmd, int type, char *arg);
void push_back_normal(t_lstcmd *cmd, int type, char *name, char *arg);
t_node *pop(t_lstcmd *cmd);
void clear(t_lstcmd *cmd);
void show(t_lstcmd *cmd);
void delete_cmd(t_node *cur);

#endif
