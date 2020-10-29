#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define MAX_THREAD 2

int a[1000], d[1000];
int n;

double wctime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1E-6 * tv.tv_usec;
}

int asc(const void *p1, const void *p2)
{
	return (*(int *)p1 - *(int *)p2);
}

int desc(const void *p1, const void *p2)
{
	return (*(int *)p2 - *(int *)p1);
}

void *sort(void *arg)
{
	char *mode = (char *)arg;
	if (mode == "a")
	{
		printf("\nAscending Order: ");
		qsort(a, n, sizeof(int), asc);
		for (int i = 0; i < n; i++)
			printf("%d ", a[i]);
	}

	if (mode == "d")
	{
		printf("\nDescending Order: ");
		qsort(d, n, sizeof(int), desc);
		for (int i = 0; i < n; i++)
			printf("%d ", d[i]);
	}
}

int main()
{
	printf("Enter number of terms for Asc/Desc sort to be generated (natural numbers): ");
	scanf("%d", &n);
	printf("\nEnter the %d elements: ", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		d[i] = a[i];
	}

	pthread_t threads[MAX_THREAD];

	double start = wctime();

	pthread_create(&threads[0], NULL, sort, "a");
	pthread_create(&threads[1], NULL, sort, "d");

	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	double end = wctime();
	printf("\n\nRun time: %f secs\n", (end - start));

	return 0;
}