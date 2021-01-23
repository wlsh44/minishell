#include "minishell.h"

int parsing_exit(t_lstcmd *cmd, char **line) {
	while (**line && !ft_isseparator(**line))
		(*line)++;
	push_back(cmd, TYPE_EXIT, NULL);
	return (0);
}