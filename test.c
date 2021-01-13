#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

char arr[500][1000];

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
#include <string.h>
#include <stdbool.h>
void init_env(char *envp[]) {
	char **buf;
	char *name;
	char *val;
	char *ptr;

	while (*envp && !(val = NULL)) {
		ptr = ft_strchr(*envp, '=');
		if (ptr == NULL || !*(ptr + 1)) {
			name = strdup(*envp);
		} else {
			*ptr++ = '\0';
			name = strdup(*envp);
			val = strdup(ptr);
		}
		printf("%s, %s\n", name, val);
		envp++;
	}
}


static bool	is_sep(char s, char sep)
{
	if (s == sep)
		return (true);
	return (false);
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


int main(int argc, char *argv[], char *env[]) {
	// char buf[PATH_MAX];
	// char *arr;

	// if (chdir("includes") < 0) {
	// 	printf("faild\n");
	// } else {
	// 	printf("%s\n", getcwd(buf, PATH_MAX));
	// }
	// if (chdir("test1") < 0) {
	// 	printf("faild\n");
	// } else {
	// 	printf("%s\n", getcwd(buf, PATH_MAX));
	// }
	//init_env(env);
	char **a;

	a = ft_split("asdf reewew", ' ');
	while (*a) {
		free(*a);
		a++;
		write(1, "bbb\n", 4);
	}
		write(1, "bbb\n", 4);

	//free(a);
}