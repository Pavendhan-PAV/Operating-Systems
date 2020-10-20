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
lli numCheck;
lli flag;

void *runner(void *arg)
{
	lli temp_num;
	temp_num = numCheck;

	lli sumPowers = 0;
	while (numCheck > 0)
	{
		lli remainder = numCheck % 10;
		sumPowers += (lli)pow(remainder, digits);
		numCheck /= 10;
	}

	if (temp_num == sumPowers)
		flag = 1;

	pthread_exit(0);
}

int main()
{
	printf("Enter upper limit for listing armstrong numbers: ");
	scanf("%llid", &n);
	double start = wctime();

	printf("ARMSTRONG NUMBERS:");
	for (lli i = 0; i < n; i++)
	{
		flag = 0;
		numCheck = i;

		digits = floor(log10(i)) + 1;

		pthread_t threads;
		pthread_create(&threads, NULL, runner, (void *)NULL);
		pthread_join(threads, NULL);

		if (flag == 1)
			printf(" %llid", i);
	}

	double end = wctime();
	printf("\nRun time: %f secs\n", (end - start));

	return 0;
}