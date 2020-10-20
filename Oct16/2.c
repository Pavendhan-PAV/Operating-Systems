#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define RD_END 0
#define WR_END 1
int main(int argc, char const *argv[])
{
	int pipefd1[2], pipefd2[2];
	int status1, status2;

	status1 = pipe(pipefd1);
	if (status1 == -1)
	{
		printf("Pipe Failed\n");
		return 0;
	}

	status2 = pipe(pipefd2);
	if (status2 == -1)
	{
		printf("Pipe Failed\n");
		return 0;
	}

	pid_t pid = fork();
	if (pid == 0)
	{
		//child
		close(pipefd1[RD_END]);
		close(pipefd2[WR_END]);
		char str1[50] = "Hello";
		char str2[50] = " World";

		char str3[50];
		memset(str3, 0, sizeof(str3));

		write(pipefd1[WR_END], str1, sizeof(str1));
		write(pipefd1[WR_END], str2, sizeof(str2));
		read(pipefd2[RD_END], str3, sizeof(str3));

		printf("Strings to be concatenated are '%s' and '%s'\n", str1, str2);
		printf("The concatenated string sent by the parent is '%s'\n", str3);
	}
	else
	{
		//parent
		close(pipefd1[WR_END]);
		close(pipefd2[RD_END]);

		char str1[50];
		char str2[50];
		memset(str1, 0, sizeof(str1));
		memset(str2, 0, sizeof(str2));
		char str3[50];
		memset(str3, 0, sizeof(str3));

		read(pipefd1[RD_END], str1, sizeof(str1));
		read(pipefd1[RD_END], str2, sizeof(str2));

		strcat(str3, str1);
		strcat(str3, str2);
		write(pipefd2[WR_END], str3, sizeof(str3));
	}
	return 0;
}