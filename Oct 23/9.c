#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long int fib = 1, fib1 = 1, fib2 = 1;
int MAX_FIB_N = 93;
int MIN_FIB_N = 1;
void *gen1(void *param);
void *gen2(void *param);

int check_and_return(int arg_count, const char *arg_value)
{
	if (arg_count < 2 || arg_count > 2)
	{
		printf("USE: ./a.out [number]\n");
		printf("Improper use. Aborting.\n");
		exit(EXIT_FAILURE);
	}

	int int_value = atoi(arg_value);

	if (int_value < MIN_FIB_N || int_value >= MAX_FIB_N)
	{
		printf("Please use an integer between [%d] and [%d]. Aborting.\n", MIN_FIB_N, MAX_FIB_N);
		exit(EXIT_FAILURE);
	}

	return int_value;
}

int main(long long int argc, char const *argv[])
{
	pthread_t tid1, tid2;
	pthread_attr_t attr1, attr2;

	long long int n = check_and_return(argc, argv[1]);

	printf("\nFIBONACCI SERIES (%d) --- \n\n0 ", atoi(argv[1]));
	printf("1 ");

	for (long long int i = 2; i <= n; i++)
	{
		long long int *nums1 = (long long int *)malloc(sizeof(long long int));
		long long int *nums2 = (long long int *)malloc(sizeof(long long int));
		nums1[0] = i - 1;
		nums2[0] = i - 2;
		pthread_attr_init(&attr1);
		pthread_create(&tid1, NULL, gen1, (void *)nums1);
		pthread_attr_init(&attr2);
		pthread_create(&tid2, NULL, gen2, (void *)nums2);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		fib = fib1 + fib2;
		printf("%lld ", fib);
	}
	printf("\n\n");
	return 0;
}
void *gen1(void *param)
{
	long long int *ar = (long long int *)param;
	long long int n = ar[0];
	long long int a = 0, b = 1, c, i;
	if (n == 0)
		fib1 = a;
	else
	{
		for (i = 2; i <= n; i++)
		{
			c = a + b;
			a = b;
			b = c;
		}
		fib1 = b;
	}
	pthread_exit(0);
}
void *gen2(void *param)
{
	long long int *ar = (long long int *)param;
	long long int n = ar[0];
	long long int a = 0, b = 1, c, i;
	if (n == 0)
		fib2 = a;
	else
	{
		for (i = 2; i <= n; i++)
		{
			c = a + b;
			a = b;
			b = c;
		}
		fib2 = b;
	}
	pthread_exit(0);
}