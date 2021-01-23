#include "minishell.h"

int parsing_cd(t_lstcmd *cmd, char **line) {
	int ret;
	char *arg;

	if (get_arg_num(*line) > 1)
		return (TOO_MANY_ARG);
	if ((ret = get_arg(line, &arg)) < 0)
		return (ret);
	push_back(cmd, TYPE_CD, arg);
	return (0);
}