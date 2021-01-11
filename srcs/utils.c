#include "minishell.h"


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
			write(1, cur->arg, ft_strlen(cur->arg));
		write(1, "\n==========\n", 12);
		cur = cur->next;
	}
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

static int	is_sep(char s, char sep)
{
	if (s == sep)
		return (1);
	return (0);
}

static int	get_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (!is_sep(*s, c) && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**get_str(char **str, const char *s, char c, int row)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (is_sep(*s, c))
			s++;
		len = get_len(s, c);
		if (!(str[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		while (!is_sep(*s, c) && *s)
		{
			str[i][j] = *s;
			j++;
			s++;
		}
		str[i++][j] = 0;
		if (*s)
			s++;
	}
	str[i] = 0;
	return (str);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		row;
	char	**str;

	i = 0;
	row = 0;
	while (s[i] != 0)
	{
		while (is_sep(s[i], c) && s[i] != 0)
			i++;
		if (s[i] != 0)
			row++;
		while (!is_sep(s[i], c) && s[i] != 0)
			i++;
	}
	if (!(str = (char **)malloc(sizeof(char *) * (row + 1))))
		return (0);
	str = get_str(str, s, c, row);
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	char	*cursur;
	int		i;

	i = 0;
	cursur = (char *)str;
	while (cursur[i] != 0)
	{
		if (cursur[i] == c)
			return (cursur + i);
		i++;
	}
	if (cursur[i] == c)
		return (cursur + i);
	return (0);
}