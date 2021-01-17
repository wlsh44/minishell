#include "minishell.h"

int parsing_pipe(t_lstcmd *cmd) {
	push_back(cmd, TYPE_PIPE, NULL);
	return (0);
}

int parsing_redirect(t_lstcmd *cmd) {
	push_back(cmd, TYPE_REDIRECT, NULL);
	return (0);
}

int parsing_double_redirect(t_lstcmd *cmd) {
	push_back(cmd, TYPE_DOUBLE_REDIRECT, NULL);
	return (0);
}