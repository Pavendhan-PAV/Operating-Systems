#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define lli long long int

double wctime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1E-6 * tv.tv_usec;
}

// Global variables
lli n;
lli digits;
//lli numCheck;
lli flag;

void *runner(void *arg)
{
	lli numCheck = *((int *)arg);
	lli temp_num = numCheck;

	lli sumPowers = 0;
	while (numCheck > 0)
	{
		lli remainder = numCheck % 10;
		sumPowers += (lli)pow(remainder, digits);
		numCheck /= 10;
	}

	if (temp_num == sumPowers)
		printf(" %lld", sumPowers);

	pthread_exit(0);
}

int main()
{
	printf("Enter upper limit for listing armstrong numbers: ");
	scanf("%llid", &n);
	double start = wctime();
	pthread_t threads[n];

	printf("ARMSTRONG NUMBERS:");
	for (lli i = 0; i < n; i++)
	{
		flag = 0;

		digits = floor(log10(i)) + 1;

		pthread_create(&threads[i], NULL, runner, &i);
	}

	for (lli i = 0; i < n; i++)
		pthread_join(threads[i], NULL);

	double end = wctime();
	printf("\nRun time: %f secs\n", (end - start));

	return 0;
}