#include "minishell.h"

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
		type = TYPE_REDIRECT_OUTPUT;
		(*line) += 1;
	} else if (!ft_strncmp(*line, "<", 1)) {
		type = TYPE_REDIRECT_INPUT;
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
		} else if (!(type == TYPE_REDIRECT_INPUT || type == TYPE_REDIRECT_OUTPUT || type == TYPE_DOUBLE_REDIRECT || type == TYPE_PIPE || type == TYPE_SEMICOLON)) {
			ret = WRONG_CMD;
			break;
		}
		if (type == TYPE_REDIRECT_OUTPUT) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_redirect_output(ms->cmd, line)) < 0)
					break;
			} else {
				ret = SYNTAX_ERROR;
				break;
			}
		}
		else if (type == TYPE_REDIRECT_INPUT) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_redirect_input(ms->cmd, line)) < 0)
					break;
			} else {
				ret = SYNTAX_ERROR;
				break;
			}
		} else if (type == TYPE_DOUBLE_REDIRECT && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_double_redirect(ms->cmd, line)) < 0)
					break;
			} else {
				ret = SYNTAX_ERROR;
				break;
			}
		} else if (type == TYPE_PIPE && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_pipe(ms->cmd)) < 0)
					break;
			} else {
				ret = SYNTAX_ERROR;
				break;
			}
		} else if (type == TYPE_SEMICOLON && (**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				(*line)++;
			} else {
				ret = SYNTAX_ERROR;
				break;
			}
		}
	}
	return (ret);
}

