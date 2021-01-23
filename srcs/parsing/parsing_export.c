#include "minishell.h"

int get_arg_export_unset(char **line, char *arg) {
	char quote;

	quote = 0;
    printf("line is: %s\n", *line);
    fflush(stdout);
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line) && **line != '=') {
		if (ft_isalpha(**line) || ft_isdigit(**line) || **line == '_' || **line == '$')
			*(arg++) = *(*line)++;
		else if (**line == '\\') {
			(*line)++;
			if (**line)
				*(arg++) = *(*line)++;
		} else if (ft_isquote(**line)) {
			quote = *(*line)++;
			while (**line && !ft_isseparator(**line) && !ft_isspace(**line) && **line != '=') {
				if (ft_isalpha(**line) || ft_isdigit(**line) || **line == '_')
					*(arg++) = *(*line)++;
				else if (**line == quote) {
					quote = 0;
					(*line)++;
					break;
				} else if (**line == '\\' && (ft_isquote((*line[1])) || (*line)[1] == '\\')) {
					(*line)++;
					*(arg++) = *(*line)++;
				} else
					return (NOT_VAILD_ARG);
			}
		}
		else
			return (NOT_VAILD_ARG);
	}
	if (**line == '=' && !quote) {
		*(arg++) = *(*line)++;
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
	}
	*arg = '\0';
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int parsing_export(t_lstcmd *cmd, char **line) {
	int arg_num;
	int size;
	char *arg;
	char *tmp;
	char *tmp2;
	int ret;

	tmp = NULL;
	while (ft_isspace(**line))
			(*line)++;
	arg_num = get_arg_num(*line);
	arg = malloc(sizeof(char));
    *arg = '\0';
	while (arg_num--) {
		size = get_arg_size(*line);
		tmp = malloc(sizeof(char) * (size + 1));
		if ((ret = get_arg_export_unset(line, tmp)) < 0) {
			free(tmp);
			return (ret);
		}
        tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
        tmp = arg;
		arg = ft_strjoin(arg, tmp2);
        free(tmp);
		free(tmp2);
		while (ft_isspace(**line))
			(*line)++;
	}
	push_back(cmd, TYPE_EXPORT, arg);
	return (0);
}