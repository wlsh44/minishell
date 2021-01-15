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



int parsing_pwd(t_lstcmd *cmd, char **line) {
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	while (ft_isspace(**line))
			(*line)++;
	push_back(cmd, TYPE_PWD, NULL);
	return (0);
}

int parsing_env(t_lstcmd *cmd, char **line) {
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	while (ft_isspace(**line))
			(*line)++;
	push_back(cmd, TYPE_ENV, NULL);
	return (0);
}



int get_arg_export_unset(char **line, char *arg) {
	char quote;

	quote = 0;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line) && **line != '=') {
		if (ft_isalpha(**line) || ft_isdigit(**line) || **line == '_')
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
	while (arg_num--) {
		size = get_arg_size(*line);
		tmp = malloc(sizeof(char) * (size + 1));
		if ((ret = get_arg_export_unset(line, tmp)) < 0) {
			free(tmp);
			return (ret);
		}
		tmp2 = ft_strjoin(tmp, " ");
		arg = ft_strjoin(arg, tmp2);
		free(tmp);
		free(tmp2);
		while (ft_isspace(**line))
			(*line)++;
	}
	push_back(cmd, TYPE_EXPORT, arg);
	return (0);
}

int parsing_unset(t_lstcmd *cmd, char **line) {
	int arg_num;
	int size;
	char *arg;
	char *tmp;
	char *tmp2;
	int ret;

	tmp = NULL;
	while (ft_isspace(**line))
			(*line)++;
	if ((arg_num = get_arg_num(*line)) == 0)
		return (NOT_ENOUGH_ARG);
	while (arg_num--) {
		size = get_arg_size(*line);
		arg = malloc(sizeof(char) * (size + 1));
		if ((ret = get_arg_export_unset(line, arg)) < 0) {
			free(arg);
			return (ret);
		}
		tmp2 = ft_strjoin(tmp, " ");
		arg = ft_strjoin(arg, tmp2);
		free(tmp);
		free(tmp2);
		while (ft_isspace(**line))
			(*line)++;
	}
	push_back(cmd, TYPE_UNSET, arg);
	return (0);
}

int parsing_exit(t_lstcmd *cmd, char **line) {
	while (**line && !ft_isseparator(**line))
		(*line)++;
	push_back(cmd, TYPE_EXIT, NULL);
	return (0);
}

int parsing_cmd(char **line) {
	char quote;
	int type;

	quote = 0;
	if (ft_isquote(**line))
		quote = *(*line)++;
	if (!ft_strncmp(*line, "cd", 2)) {
		type = TYPE_CD;
		(*line) += 2;
	}
	else if (!ft_strncmp(*line, "pwd", 3)) {
		type = TYPE_PWD;
		(*line) += 3;
	} else if (!ft_strncmp(*line, "echo", 4)) {
		type = TYPE_ECHO;
		(*line) += 4;
	} else if (!ft_strncmp(*line, "export", 6)) {
		type = TYPE_EXPORT;
		(*line) += 6;
	} else if (!ft_strncmp(*line, "env", 3)) {
		type = TYPE_ENV;
		(*line) += 3;
	} else if (!ft_strncmp(*line, "unset", 5)) {
		type = TYPE_UNSET;
		(*line) += 5;
	} else if (!ft_strncmp(*line, "exit", 4)) {
		type = TYPE_EXIT;
		(*line) += 4;
	} else if (!ft_strncmp(*line, ">>", 2)) {
		type = TYPE_DOUBLE_REDIRECT;
		(*line) += 2;
	} else if (!ft_strncmp(*line, ">", 1)) {
		type = TYPE_REDIRECT;
		(*line) += 1;
	} else if (!ft_strncmp(*line, "|", 1)) {
		type = TYPE_PIPE;
		(*line) += 1;
	} else if (!ft_strncmp(*line, ";", 1)) {
		type = TYPE_SEMICOLON;
		(*line) += 1;
	} else {
		type = WRONG_CMD;
	}
	if (quote) {
		if (*(*line)++ != quote)
			type = WRONG_QUOTE;
	}
	return (type);
}

int parsing_redirect(t_lstcmd *cmd) {
	push_back(cmd, TYPE_REDIRECT, NULL);
	return (0);
}

int parsing_double_redirect(t_lstcmd *cmd) {
	push_back(cmd, TYPE_DOUBLE_REDIRECT, NULL);
	return (0);
}

int parsing_pipe(t_lstcmd *cmd) {
	push_back(cmd, TYPE_PIPE, NULL);
	return (0);
}

int parsing(t_minishell *ms) {
	int ret;
	int type;
	char **line;

	line = &ms->cmd_line;
	while (**line && !(ret = 0)) {
		while (ft_isspace(**line))
			(*line)++;
		if ((type = parsing_cmd(line)) < 0)
			return (type);
		if (type == TYPE_CD && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_cd(ms->cmd, line)) < 0)
				break;
		}
		else if (type == TYPE_PWD && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_pwd(ms->cmd, line)) < 0)
				break;
		}
		else if (type == TYPE_ECHO && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_echo(ms->cmd, line)) < 0)
				break;
			//printf(">>>>>>>> %s|\n", *line);
		} else if (type == TYPE_EXPORT && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_export(ms->cmd, line)) < 0)
				break;
		}
		else if (type == TYPE_ENV && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_env(ms->cmd, line)) < 0)
				break;
		} else if (type == TYPE_UNSET && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_unset(ms->cmd, line)) < 0)
				break;
		} else if (type == TYPE_EXIT && (!**line || ft_isspace((**line)) || ft_isseparator((**line)))) {
			if ((ret = parsing_exit(ms->cmd, line)) < 0)
				break;
		} else if (!(type == TYPE_REDIRECT || type == TYPE_DOUBLE_REDIRECT || type == TYPE_PIPE || type == TYPE_SEMICOLON)) {
			ret = WRONG_CMD;
			break;
		}
		if (type == TYPE_REDIRECT) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_redirect(ms->cmd)) < 0)
					break;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		} else if (type == TYPE_DOUBLE_REDIRECT && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_double_redirect(ms->cmd)) < 0)
					break;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		} else if (type == TYPE_PIPE && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_pipe(ms->cmd)) < 0)
					break;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		} else if (type == TYPE_SEMICOLON && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				(*line)++;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		}
	}
	return (ret);
}

