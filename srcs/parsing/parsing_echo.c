#include "minishell.h"

int check_echo_option(char **line) {
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '-' && (*line)[1] == 'n' && ft_isspace((*line)[2])) {
		(*line) += 2;
		return (1);
	}
	return 0;
}

int get_arg_char_echo(char **line, char *arg) {
	char quote;

	quote = 0;
	while (ft_isspace(**line))
		(*line)++;
	while (**line && !ft_isseparator(**line)) {
		if (**line == '\\') {
			(*line)++;
			if (**line)
				*(arg++) = *(*line)++;
		} else if (ft_isquote(**line)) {
			quote = *(*line)++;
			while (**line && !ft_isseparator(**line)) {
				if (**line == quote) {
					quote = 0;
					(*line)++;
					break;
				} else if (**line == '\\' && (ft_isquote((*line[1])) || (*line)[1] == '\\'))
					(*line)++;
				*(arg++) = *(*line)++;
			}
		} else
			*(arg++) = *(*line)++;
	}
	while (ft_isspace(*(arg - 1)))
		arg--;
	*arg = '\0';
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int get_arg_size_echo(char *line) {
	int size;

	size = 0;
	while (ft_isspace(*line))
		line++;
	while (*line && !ft_isseparator(*line)) {
		size++;
		line++;
	}
	return (size);
}

int get_arg_echo(char **line, char **arg) {
	int size;
	int ret;
	char *tmp;

	size = get_arg_size_echo(*line);
	tmp = malloc(sizeof(char) * (size + 1));
	if ((ret = get_arg_char_echo(line, tmp)) < 0) {
		free(tmp);
		return (ret);
	}
	*arg = tmp;
	return (ret);
}

int parsing_echo(t_lstcmd *cmd, char **line) {
	int ret;
	int type;
	char *arg;

	type = check_echo_option(line) ? TYPE_ECHO_N : TYPE_ECHO;
	if ((ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	push_back(cmd, type, arg);
	return (0);
}