#include "minishell.h"

int parsing_env(t_lstcmd *cmd, char **line) {
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	while (ft_isspace(**line))
			(*line)++;
	push_back(cmd, TYPE_ENV, NULL);
	return (0);
}
