#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TOO_MANY_ARG -2
#define WRONG_QUOTE -3
#define TYPE_CD 1
#define TYPE_PWD 2
#define TYPE_ECHO 3
#define TYPE_ECHO_N 4

/*
cd
echo
pwd
exit
export
env
unset
|
<
>
>>
;
*/

/*
1) 'test' "test" -> test x     'test' -> 2)error 
2) \가 들어왔을 때                 a) 무시 te\st -> test, te\\st -> te\st
3) echo의 -n 을 어디서 담아둘지 	 새로운 type
4) name이 필요한가? x
5) 
*/

typedef struct s_node {
	//char *name;
	char *arg;
	int type;
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct {
	t_node *head;
	t_node *tail;
} t_lstcmd;

typedef struct {
	t_lstcmd *cmd;
	char *cmd_line;
	int err;
} t_minishell;

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

void show(t_lstcmd *cmd) {
	t_node *cur;

	cur = cmd->head->next;
	while (cur != cmd->tail) {
		printf("TYPE: %d\nARG: %s\n", cur->type, cur->arg);
		cur = cur->next;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s)
	{
		i++;
	}
	return (i);
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
		if (*line == '\\' && (ft_isquote(line + 1) || *(line + 1) == '\\')) {
			size++;
			line += 2;
		} else {
			if (!ft_isquote(*line))
				size++;
			line++;
		}
	}
	return (size);
}

int get_arg_char(char **line, char *arg) {
	int flag;
	char quote;
	
	flag = 1;
	while (ft_isspace(**line))
		(*line)++;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line)) {
		if (**line == '\\') {
			(*line)++;
			if (**line == '\\' || ft_isquote(**line)) {
				*(arg++) = *(*line)++;
			}
		} else if (ft_isquote(**line)) {
			quote = **line;
			if (**line == quote) {
				(*line)++;
				flag = 0;
				while (**line && !ft_isseparator(**line) && !ft_isspace(**line)) {
					if (**line != quote) {
						flag = 1;
						break;
					} else if (**line == '\\') {
						*(arg++) = *(*line)++;
						while (**line == '\\')
							(*line)++;
					} else {
						*(arg++) = *(*line)++;
					}
				}
			}
		}
	}
	while (ft_isspace(**line))
		(*line)++;
	*arg = '\0';
	if (!flag)
		return (WRONG_QUOTE);
	return (0);
}

int get_arg(char **line, char **arg) {
	int size;
	int ret;
	char *tmp;

	size = get_arg_size(*line);
	tmp = malloc(sizeof(char) * (size + 1));
	if ((ret = get_arg_char(line, tmp)) < 0)
		return (ret);
	*arg = tmp;
	return (0);
}

int parsing_cd(t_lstcmd *cmd, char **line) {
	int ret;
	char *arg;

	(*line) += 2;
	if (get_arg_num(*line) > 1)
		return (TOO_MANY_ARG);
	if ((ret = get_arg(line, &arg) < 0))
		return (ret);
	push_back(cmd, TYPE_CD, arg);
	return (0);
}

int check_echo_type(char **line) {
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '-' && (*line)[1] == 'n' && ft_isspace((*line)[2])) {
		(*line) += 2;
		return (1);
	}
	return 0;
}

int parsing_echo(t_lstcmd *cmd, char **line) {
	int ret;
	int type;
	char *arg;

	(*line) += 2;
	type = check_echo_option(line) ? TYPE_ECHO_N : TYPE_ECHO;
	if (get_arg_num(*line) > 1)
		return (TOO_MANY_ARG);
	if ((ret = get_arg(line, &arg) < 0))
		return (ret);
	push_back(cmd, type, arg);
	return (0);
}

void cmd_error(int err) {
	if (err == TOO_MANY_ARG) {
		write(1, "too many arg\n", 13);
	} else if (err == WRONG_QUOTE) {
		write(1, "wrong quote\n", 12);
	}
}

int parsing_pwd(t_lstcmd *cmd, char **line) {
	(*line) += 3;
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	push_back(cmd, TYPE_PWD, NULL);
	return (0);
}

int parsing_export(t_lstcmd *cmd, char **line) {
	int arg_num;
	int size;

	arg_num = get_arg_num(*line);
	while ()
}

int parsing(t_minishell *ms) {
	int ret;
	char **line;

	line = &ms->cmd_line;
	while (*line && !(ret = 0)) {
		while (ft_isspace(*line))
			(*line)++;
		//command파싱해야됨 ex) "env"
		if ((ft_strncmp(*line, "cd", 2) == 0) && (!(*line)[2] || ft_isspace((*line)[2]))) {
			if ((ret = parsing_cd(ms->cmd, line)) < 0)
				break;
		}
		else if ((ft_strncmp(*line, "pwd", 3) == 0) && (!(*line)[3] || ft_isspace((*line)[3]))) {
			if ((ret = parsing_pwd(ms->cmd, line)) < 0)
				break;
		}
		else if ((ft_strncmp(*line, "echo", 4) == 0) && (!(*line)[4] || ft_isspace((*line)[4]))) {
			if ((ret = parsing_echo(ms->cmd, line)) < 0)
				break;
		} else if ((ft_strncmp(*line, "export", 3) == 0) && (!(*line)[3] || ft_isspace((*line)[3]))) {
			if ((ret = parsing_export(ms->cmd, line)) < 0)
				break;
		}
		else if ((ft_strncmp(*line, "env", 3) == 0) && (!(*line)[3] || ft_isspace((*line)[3]))) {
			if ((ret = parsing_env(ms->cmd, line)) < 0)
				break;
		} else if ((ft_strncmp(*line, "unset", 5) == 0) && (!(*line)[5] || ft_isspace((*line)[5]))) {
			if ((ret = parsing_unset(ms->cmd, line)) < 0)
				break;
		} else if ((ft_strncmp(*line, "exit", 4) == 0) && (!(*line)[4] || ft_isspace((*line)[4]))) {
			if ((ret = parsing_exit(ms->cmd, line)) < 0)
				break;
		}
	}
	if (ret < 0)
		cmd_error(ret);
	return (0);
}

int main() {
	t_minishell ms;
	
	char *line = "cd test";
	char *l2 = "cd";
	char *l3 = "cd  test";
	char *l4 = "  cd  test";
	char *l5 = "cd test   ";
	char *l6 = "cd \"test\"";
	char *l7 = "cd atg atg";
	char *l8 = "pwd";
	char *l9 = "pwd \'\'";

	ms.cmd = malloc(sizeof(ms.cmd));
	ms.cmd->head = malloc(sizeof(t_node));
	ms.cmd->tail = malloc(sizeof(t_node));
	ms.cmd->head->prev = NULL;
	ms.cmd->head->next = ms.cmd->tail;
	ms.cmd->tail->prev = ms.cmd->head;
	ms.cmd->tail->next = NULL;
	char *test;

	//test = "cd";
	//printf("%s\n", test);
	// t_node node1 = {"asdf"};
	// t_node node2 = {"qwer"};
	// push_back(ms.cmd, &node1);
	// push_back(ms.cmd, &node2);
	//show(ms.cmd);
	// parsing(ms.cmd, &line);
	// parsing(ms.cmd, &l2);
	// parsing(ms.cmd, &l3);
	// parsing(ms.cmd, &l4);
	// parsing(ms.cmd, &l5);
	// parsing(ms.cmd, &l6);
	// parsing(ms.cmd, &l7);
	parsing(&ms);
	parsing(&ms);
	show(ms.cmd);
}