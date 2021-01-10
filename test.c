#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
int main(int argc, char *argv[], char *env[]) {
	char buf[PATH_MAX];

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
	while (*env) {
		printf("%s\n", *env);
		env++;
	}
}