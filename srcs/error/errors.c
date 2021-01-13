#include "minishell.h"

void cmd_error(int err) {
	if (err == TOO_MANY_ARG) {
		write(1, "too many arg\n", 13);
	} else if (err == WRONG_QUOTE) {
		write(1, "wrong quote\n", 12);
	} else if (err == NOT_ENOUGH_ARG) {
		write(1, "not enough arg\n", 15);
	} else if (err == NOT_VAILD_ARG) {
		write(1, "not vaild arg\n", 13);
	} else if (err == WRONG_CMD) {
		write(1, "wrong cmd\n", 10);
	} else if (err == SYNTAX_ERROR) {
		write(1, "syntax error\n", 13);
	}
}

void execute_error(int err) {
	if (err == NOT_VAILD_IDENTIFIER)
		write(1, "not a vaild identifier\n", 24);
	else if (err == NO_DIRECTORY) {
		write(1, "no such file or directory\n", 27);
	}
}