#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define size 20

typedef struct qsort_starter
{
	int *arr;
	int low;
	int high;
	int depthOfThreadCreation;
} quickSort_parameters;

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *arr, int low, int high, int pivot)
{
	int pivotValue = arr[pivot];
	swap(&arr[pivot], &arr[high]);
	int s = low;

	for (int i = low; i < high; i++)
	{
		if (arr[i] <= pivotValue)
		{
			swap(&arr[i], &arr[s]);
			s++;
		}
	}
	swap(&arr[s], &arr[high]);
	return s;
}

void quickSort(int *arr, int low, int high)
{
	if (low < high)
	{
		int pivotPosition = low + (high - low) / 2;
		pivotPosition = partition(arr, low, high, pivotPosition);
		quickSort(arr, low, pivotPosition - 1);
		quickSort(arr, pivotPosition + 1, high);
	}
}

void concurrent_quickSort(int *arr, int low, int high, int depthOfThreadCreation);

void *worker_quickSort(void *initialValues)
{
	quickSort_parameters *parameters = initialValues;
	concurrent_quickSort(parameters->arr, parameters->low, parameters->high, parameters->depthOfThreadCreation);
	return NULL;
}

void concurrent_quickSort(int *arr, int low, int high, int depthOfThreadCreation)
{
	if (low < high)
	{

		int pivotPos = low + (high - low) / 2;
		pivotPos = partition(arr, low, high, pivotPos);
		pthread_t thread;

		if (depthOfThreadCreation > 0)
		{
			quickSort_parameters thread_param = {arr, low, pivotPos - 1, depthOfThreadCreation};
			int result;
			result = pthread_create(&thread, NULL, worker_quickSort, &thread_param);
			concurrent_quickSort(arr, pivotPos + 1, high, depthOfThreadCreation);
			pthread_join(thread, NULL);
		}
		else
		{
			quickSort(arr, low, pivotPos - 1);
			quickSort(arr, pivotPos + 1, high);
		}
	}
}

int main()
{
	int depthOfThreadCreation = 4;

	int *arrayElements = malloc((size * sizeof(int)));

	for (int i = 0; i < size; i++)
		arrayElements[i] = rand() % 100;

	printf("\nUnsorted array: ");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arrayElements[i]);
	}

	clock_t t1, t2;

	//-------------------------------------------------------------------------

	t1 = clock();
	concurrent_quickSort(arrayElements, 0, size - 1, depthOfThreadCreation);
	t2 = clock();

	printf("\n");
	printf("\nParallely Sorted array: ");

	for (int i = 0; i < size; i++)
		printf("%d ", arrayElements[i]);
	printf("\nRun time: %f\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

	//-------------------------------------------------------------------------

	t1 = clock();
	quickSort(arrayElements, 0, size - 1);
	t2 = clock();

	printf("\nSerially Sorted array: ");

	for (int i = 0; i < size; i++)
		printf("%d ", arrayElements[i]);
	printf("\nRun time: %f\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

	//-------------------------------------------------------------------------

	printf("\n");
	free(arrayElements);
	return 0;
}