#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

void push_back(t_lstcmd *cmd, int type, char *arg);
t_node *pop(t_lstcmd *cmd);
void clear(t_lstcmd *cmd);
void show(t_lstcmd *cmd);

#endif