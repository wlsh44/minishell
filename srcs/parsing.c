#include "../includes/minishell.h"

void push_back(t_lstcmd *cmd, int type, char *arg) {
	t_node *node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->arg = arg;
	node->prev = cmd->tail->prev;
	node->next = cmd->tail;
	cmd->tail->prev->next = node;
	cmd->tail->prev = node;
}

t_node *pop(t_lstcmd *cmd) {
	return (cmd->head->next);
}

void clear(t_lstcmd *cmd) {
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail) {
		cur = cur->next;
		if (cur->prev->arg) {
			free(cur->prev->arg);
			cur->prev->arg = NULL;
		}
		free(cur->prev);
		cur->prev = NULL;
	}
	cmd->head->next = cmd->tail;
	cmd->tail->prev = cmd->head;
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nnbr;
	long	power;
	int		size;
	int		sign;

	sign = (n < 0) ? -1 : 1;
	nnbr = n;
	power = 10;
	size = (n < 0) ? 2 : 1;
	while (n /= 10)
		power = power * 10 + (0 * size++);
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	nnbr *= sign;
	size = (sign < 0) ? 1 : 0;
	while (power /= 10)
		str[size++] = ((nnbr / power) % 10) + 48;
	if (sign == -1)
		str[0] = '-';
	str[size] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s++)
	{
		i++;
	}
	return (i);
}
#include <string.h>
void show(t_lstcmd *cmd) {
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail) {
		//printf("TYPE: %d\nARG: %s\n", cur->type, cur->arg);
		write(1, "TYPE: ", 6);
		write(1, ft_itoa(cur->type), 1);
		write(1, "\nARG: ", 6);
		if (cur->arg)
			write(1, cur->arg, strlen(cur->arg));
		write(1, "\n==========\n", 12);
		cur = cur->next;
	}
}



char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*arr;

	len = ft_strlen(s);
	if (!(arr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	char *pt;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	pt = str;
	while (*s1)
		*pt++ = *s1++;
	while (*s2)
		*pt++ = *s2++;
	*pt = '\0';
	return (str);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	if (n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

int		ft_isspace(char c)
{
	return ((c == '\t' || c == '\v' || c == '\n' ||
c == '\r' || c == '\f' || c == ' '));
}

int		ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		ft_isseparator(char c)
{
	return ((c == ';' || c == '|' || c == '<' || c == '>'));
}

int		ft_isquote(char c)
{
	return ((c == '\'' || c == '"'));
}

int		ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}


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
/*
\
\\
\"
\'
*/
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
	} else if (err == SYSTAX_ERROR) {
		write(1, "syntax error\n", 13);
	}
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
		} else if (type == TYPE_DOUBLE_REDIRECT && (!**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_double_redirect(ms->cmd)) < 0)
					break;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		} else if (type == TYPE_PIPE && (!**line || ft_isspace((**line)))) {
			if (**line && !ft_isseparator(**line)) {
				if ((ret = parsing_pipe(ms->cmd)) < 0)
					break;
			} else {
				ret = SYSTAX_ERROR;
				break;
			}
		} else if (type == TYPE_SEMICOLON && (!**line || ft_isspace((**line)))) {
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

