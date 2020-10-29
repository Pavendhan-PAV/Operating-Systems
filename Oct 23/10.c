#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int L[100][100];
char lcs[100];

void *gen(void *param)
{
	char **argv = (char **)param;

	char *X = argv[1];
	char *Y = argv[2];
	int m = strlen(argv[1]);
	int n = strlen(argv[2]);
	int index = L[m][n];

	lcs[index] = '\0';
	int i = m, j = n;

	while (i > 0 && j > 0)
	{
		if (X[i - 1] == Y[j - 1])
		{
			lcs[index - 1] = X[i - 1]; // Put current character in result
			i--;
			j--;
			index--; // reduce values of i, j and index
		}
		else if (L[i - 1][j] > L[i][j - 1])
			i--;
		else
			j--;
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	if (argc < 3 || argc > 3)
	{
		printf("USE: ./a.out [str1] [str2]\n");
		printf("Improper use. Aborting.\n");
		exit(EXIT_FAILURE);
	}
	memset(L, -1, sizeof(L));

	pthread_t tid;
	pthread_attr_t attr;

	int m = strlen(argv[1]);
	int n = strlen(argv[2]);
	char *X = argv[1];
	char *Y = argv[2];

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;
			else
			{
				if (L[i - 1][j] > L[i][j - 1])
					L[i][j] = L[i - 1][j];
				else
					L[i][j] = L[i][j - 1];
				//L[i][j] = max(L[i - 1][j], L[i][j - 1]);
			}
		}
	}
	pthread_attr_init(&attr);
	pthread_create(&tid, NULL, gen, (void *)argv);
	pthread_join(tid, NULL);
	//cout << "LCS of " << X << " and " << Y << " is " << lcs << endl;
	printf("\nLongest Common Substring of '%s' and '%s' is '%s'\n\n", X, Y, lcs);
	return 0;
}