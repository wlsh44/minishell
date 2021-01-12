#include "minishell.h"
#include <stdio.h>

int execute_cd(t_minishell *ms, t_node *cur) {
	if (ft_strcmp(cur->arg, "") == 0) {

	}
}

int	execute_exit(t_minishell *ms)
{
	ft_exit(ms);
}

int	execute_echo(t_node *node)
{
	return (ft_echo(node));
}

int	execute_pwd(t_node *node)
{
	return (ft_pwd(node));
}

int execute(t_minishell *ms) {
	t_node *cur;
	int ret;

	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0)) {
		if (cur->type == TYPE_EXIT)
		{
			ret = execute_exit(ms);
			return (0);
		}
		else if (cur->type == TYPE_ECHO || cur->type == TYPE_ECHO_N)
		{
			ret = execute_echo(cur);
			return (ret);
		}
		else if (cur->type == TYPE_PWD)
		{
			ret = execute_pwd(cur);
			return (ret);
		}
	}
	return (1);
}
