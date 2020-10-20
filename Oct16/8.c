#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ll unsigned long long int

double wctime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1E-6 * tv.tv_usec;
}

int MAX_FIB_N = 93;
int MIN_FIB_N = 1;

int fib_num;
ll *fib_seq;

void *thread_runner(void *arg)
{
	for (int element = 2; element < fib_num; element++)
		fib_seq[element] = fib_seq[element - 2] + fib_seq[element - 1];
	pthread_exit(EXIT_SUCCESS);
}

int check_and_return(int arg_count, const char *arg_value)
{
	if (arg_count < 2 || arg_count > 2)
	{
		printf("USE: ./a.out [number]\n");
		printf("Improper use. Aborting.\n");
		exit(EXIT_FAILURE);
	}

	int int_value = atoi(arg_value);

	if (int_value < MIN_FIB_N || int_value > MAX_FIB_N)
	{
		printf("Please use an integer between [%d] and [%d]. Aborting.\n", MIN_FIB_N, MAX_FIB_N);
		exit(EXIT_FAILURE);
	}

	return int_value;
}

void print_int_array(ll *array, int array_size)
{
	for (ll i = 0; i < array_size; i++)
		printf("%lld ", array[i]);
	printf("\n");
	return;
}

int main(int argc, char const *argv[])
{
	fib_num = check_and_return(argc, argv[1]);

	fib_seq = (ll *)malloc(sizeof(ll) * (fib_num));

	if (fib_seq == NULL)
	{
		printf("Could not create array. Aborting.\n");
		exit(EXIT_FAILURE);
	}

	fib_seq[0] = 0;
	fib_seq[1] = 1;

	pthread_t thread;

	double start = wctime();

	if (pthread_create(&thread, NULL, thread_runner, NULL))
	{
		printf("Could not create thread. Aborting.\n");
		return EXIT_FAILURE;
	}
	if (pthread_join(thread, NULL))
	{
		printf("Could not join thread. Aborting.\n");
		return EXIT_FAILURE;
	}
	double end = wctime();

	print_int_array(fib_seq, fib_num);
	printf("Run time: %f secs\n", (end - start));

	// Uses [free()] to cleanup allocated memory of integer arrays.
	free(fib_seq);
	if (fib_seq != NULL)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}