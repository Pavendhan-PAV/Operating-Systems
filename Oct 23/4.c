#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>
#define ll long long
#define MIN_LIM 2
#define MAX_LIM 32722

struct node
{
	ll int index;
};

ll int pno[32720];

void *prime(void *arg)
{
	int flag = 0;
	struct node *temp = ((struct node *)arg);
	ll int n = temp->index;

	if (n <= 1)
		flag = 1;

	for (ll int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
			flag = 1;
	}

	if (flag != 1)
		pno[n] = 1;
	pthread_exit(NULL);
}

void print(ll int n)
{
	struct node *p = (struct node *)malloc(n * sizeof(struct node));

	printf("Prime Numbers: ");
	pthread_t pth[n + 1];

	for (ll int i = 2; i <= n; i++)
	{
		p[i].index = i;
		pthread_create(&pth[i], NULL, prime, &p[i]);
	}

	for (ll int i = 2; i <= n / 2; i++)
		pthread_join(pth[i], NULL);

	for (ll int i = 2; i < n; i++)
	{
		if (pno[i] == 1)
			printf("%lld ", i);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage ./a.out [Upper limit number]\n");
		printf("Improper use.\nAborting.\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	if (n < MIN_LIM || n > MAX_LIM)
	{
		printf("RANGE: 2 - 10232.\nAborting.\n");
		exit(EXIT_FAILURE);
	}
	memset(&pno, 0, sizeof(pno));

	print(n);
	printf("\n");

	return 0;
}