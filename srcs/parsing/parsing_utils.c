#include "minishell.h"

int get_arg_num(char *line) {
	int arg_num;
	int flag;

	flag = 0;
	arg_num = 0;
	while (*line && !ft_isseparator(*line)) {
		if (ft_isspace(*line)) {
			flag = 0;
			while (ft_isspace(*line))
				line++;
		} else {
			if (!flag) {
				flag = 1;
				arg_num++;
			}
			line++;
		}
	}
	return (arg_num);
}

int get_arg_size(char *line) {
	int size;

	size = 0;
	while (ft_isspace(*line))
		line++;
	while (*line && !ft_isseparator(*line) && !ft_isspace(*line)) {
		size++;
		line++;
	}
	return (size);
}

int get_arg_char(char **line, char *arg) {
	char quote;

	quote = 0;
	while (ft_isspace(**line))
		(*line)++;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line)) {
		if (**line == '\\') {
			(*line)++;
			if (**line)
				*(arg++) = *(*line)++;
		} else if (ft_isquote(**line)) {
			quote = *(*line)++;
			while (**line && !ft_isseparator(**line) && !ft_isspace(**line)) {
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
	while (ft_isspace(**line))
		(*line)++;
	*arg = '\0';
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int get_arg(char **line, char **arg) {
	int size;
	int ret;
	char *tmp;

	size = get_arg_size(*line);
	tmp = malloc(sizeof(char) * (size + 1));
	if ((ret = get_arg_char(line, tmp)) < 0) {
		free(tmp);
		return (ret);
	}
	*arg = tmp;
	return (ret);
}