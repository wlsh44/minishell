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

int main(int argc, char *argv[], char *env[]) {
	char buf[PATH_MAX];
	char *arr;
	//strlen(NULL);
	// if (chdir("test") < 0) {
	// 	printf("faild\n");
	// } else {
	// 	printf("%s\n", getcwd(buf, PATH_MAX));
	// }
	// if (chdir("test1") < 0) {
	// 	printf("faild\n");
	// } else {
	// 	printf("%s\n", getcwd(buf, PATH_MAX));
	// }
	init_env(env);
}