#ifndef EXECUTE_H
#define EXECUTE_H

#include "minishell.h"

int	execute(t_minishell *ms);
int	ft_exit(t_minishell *ms);
int	ft_echo(t_node *node);
int	ft_pwd(t_node *node);
int	ft_cd(t_minishell *ms, t_node *cur);
int	ft_env(t_minishell *ms);
int	ft_export(t_minishell *ms, t_node *cur);
int	ft_unset(t_minishell *ms, t_node *cur);

#endif
