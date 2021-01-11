#ifndef ENV_H
#define ENV_H

#include "minishell.h"

void push_back_env(t_lstenv *env, char *name, char *val);
void init_env(t_minishell *ms, char *envp[]);

#endif