#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define LIM 20
#define THREAD_LIM 4

int a[LIM];
int part = 0;

void merge(int low, int mid, int high)
{
	int *left = new int[mid - low + 1];
	int *right = new int[high - mid];

	int n1 = mid - low + 1, n2 = high - mid, i, j;

	for (i = 0; i < n1; i++)
		left[i] = a[i + low];
	for (i = 0; i < n2; i++)
		right[i] = a[i + mid + 1];

	int k = low;
	i = j = 0;

	// merge left and right in ascending order
	while (i < n1 && j < n2)
	{
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}

	while (i < n1)
		a[k++] = left[i++];
	while (j < n2)
		a[k++] = right[j++];
}

void merge_sort(int low, int high)
{
	int mid = low + (high - low) / 2;
	if (low < high)
	{
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

void *merge_sort(void *arg)
{
	int thread_part = part++;

	int low = thread_part * (LIM / 4);
	int high = (thread_part + 1) * (LIM / 4) - 1;

	int mid = low + (high - low) / 2;
	if (low < high)
	{
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
	pthread_exit(NULL);
}

int main()
{
	for (int i = 0; i < LIM; i++)
		a[i] = rand() % 100;

	printf("Unsorted array: ");
	for (int i = 0; i < LIM; i++)
		printf("%d ", a[i]);

	clock_t t1, t2;

	//-------------------------------------------------------------------------

	t1 = clock();
	pthread_t threads[THREAD_LIM];

	for (int i = 0; i < THREAD_LIM; i++)
		pthread_create(&threads[i], NULL, merge_sort, (void *)NULL);
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);

	merge(0, (LIM / 2 - 1) / 2, LIM / 2 - 1);
	merge(LIM / 2, LIM / 2 + (LIM - 1 - LIM / 2) / 2, LIM - 1);
	merge(0, (LIM - 1) / 2, LIM - 1);
	t2 = clock();

	printf("\n\nParallely Sorted array: ");
	for (int i = 0; i < LIM; i++)
		printf("%d ", a[i]);
	printf("\nRun time: %f\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

	//--------------------------------------------------------------------------

	t1 = clock();
	merge_sort(0, LIM - 1);
	printf("\nSerially Sorted array: ");
	for (int i = 0; i < LIM; i++)
		printf("%d ", a[i]);
	t2 = clock();

	printf("\nRun time: %f\n", (t2 - t1) / (double)CLOCKS_PER_SEC);
	return 0;
}
