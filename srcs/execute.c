#include "minishell.h"

int execute_cd(t_minishell *ms) {
	
}

int execute(t_minishell *ms) {
	t_node *cur;
	int ret;

	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0)) {
		if (cur == TYPE_CD)
			ret = execute_cd(ms);
	}
}