#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define MAX_THREAD 2

int a[1000], occ[1000];
int n;
int key;
int found = 0;
int part = 0;
int ind;

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

void *binary_search(void *arg)
{
	int low, high, mid;
	if (part == 0)
	{
		low = 0;
		high = n / 2;
		part++;
	}
	else
	{
		low = n / 2 + 1;
		high = n - 1;
	}

	while (low <= high && !found)
	{
		mid = (high - low) / 2 + low;

		if (a[mid] == key)
		{
			found = 1;
			ind = mid;
			break;
		}
		else if (a[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
}

void *Occurrences(void *arg)
{
	binary_search((void *)NULL);

	if (ind == -1)
	{
		printf("\nOccurrences of %d in the array(indices): NO OCCURRENCE", key);
		return 0;
	}

	int k = 0;
	occ[k++] = ind + 1;

	int count = 1;
	int left = ind - 1;
	while (left >= 0 && a[left] == key)
	{
		occ[k++] = left + 1;
		count++, left--;
	}
	int right = ind + 1;
	while (right < n && a[right] == key)
	{
		occ[k++] = right + 1;
		count++, right++;
	}

	qsort(occ, k, sizeof(int), asc);
	printf("\nOccurrences of %d in the array(indices): ", key);

	for (int i = 0; i < k; i++)
		printf("%d ", occ[i]);
	printf("\nTotal count: %d\n", count);
}

int main()
{
	printf("Enter number of terms for multiprocessing version of binary search (natural numbers): ");
	scanf("%d", &n);
	printf("\nEnter the %d elements: ", n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	qsort(a, n, sizeof(int), asc);
	printf("\nSorted array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);

	printf("\n\nEnter the number to be searched for: ");
	scanf("%d", &key);

	pthread_t threads[MAX_THREAD + 1];

	double start = wctime();

	for (int i = 0; i < MAX_THREAD; i++)
		pthread_create(&threads[i], NULL, binary_search, (void *)NULL);

	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	if (found)
		printf("%d found in the array.\n", key);
	else
		printf("%d not found in the array.\n", key);

	pthread_create(&threads[MAX_THREAD], NULL, Occurrences, (void *)NULL);
	pthread_join(threads[MAX_THREAD], NULL);

	double end = wctime();
	printf("\nRun time: %f secs\n", (end - start));

	return 0;
}
