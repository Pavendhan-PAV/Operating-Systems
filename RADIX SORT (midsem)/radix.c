#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

int arrradix[200000];
int array[200000];

void generate(int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		arrradix[i] = rand() % 101;
		array[i] = rand() % 101;
	}
}

struct data
{
	int arr[200000];
	int n;
};

struct count_sort_data
{
	struct data *d;
	int exp;
};

int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

void *countSort(void *param)
{
	struct count_sort_data *cs = (struct count_sort_data *)param;

	int output[(cs->d)->n]; // output array
	int i, count[10] = {0};

	for (i = 0; i < (cs->d)->n; i++)
		count[((cs->d)->arr[i] / cs->exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = (cs->d)->n - 1; i >= 0; i--)
	{
		output[count[((cs->d)->arr[i] / cs->exp) % 10] - 1] = (cs->d)->arr[i];
		count[((cs->d)->arr[i] / cs->exp) % 10]--;
	}

	for (i = 0; i < (cs->d)->n; i++)
		(cs->d)->arr[i] = output[i];

	print((cs->d)->arr, (cs->d)->n);
	pthread_exit(0);
}

void *RadixSort(void *param)
{
	struct data *d = param;
	int m = getMax(d->arr, d->n);
	int thread_count = 0;

	printf("\nEnter number of threads: ");
	scanf("%d", &thread_count);

	printf("\nPasses for Radix Sort: \n");

	struct count_sort_data cd[thread_count];
	pthread_t tid[thread_count];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int i = 0;
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		cd[i].d = d;
		cd[i].exp = exp;
		pthread_create(&tid[i], &attr, countSort, &cd[i]);
		i++;
	}
	for (int j = 0; j < i; ++j)
	{
		pthread_join(tid[j], NULL);
		j++;
	}
	pthread_exit(0);
}

void *BubbleSort(void *param)
{
	struct data *d = param;
	printf("\nPasses for Bubble Sort: \n");
	for (int i = 1; i < d->n; i++)
	{
		int tcheck = 0;
		for (int j = 0; j < d->n - i; j++)
		{
			if (d->arr[j] > d->arr[j + 1])
			{
				int temp = d->arr[j];
				d->arr[j] = d->arr[j + 1];
				d->arr[j + 1] = temp;
				tcheck = 1;
			}
		}
		print(d->arr, d->n);
		if (tcheck == 0)
			break;
	}

	pthread_exit(0);
}

void *InsertionSort(void *param)
{
	struct data *d = param;
	printf("\nPasses for Insertion Sort: \n");
	for (int i = 1; i < d->n; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (d->arr[j - 1] > d->arr[j])
			{
				int temp = d->arr[j];
				d->arr[j] = d->arr[j - 1];
				d->arr[j - 1] = temp;
			}
			else
				break;
		}
		print(d->arr, d->n);
	}

	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	clock_t t1, t2;

	if (argc != 2)
	{
		printf("Usage: ./a.out <SIZE>\nAborting.\n");
		exit(EXIT_FAILURE);
	}

	else
	{
		int n = atoi(argv[1]);
		printf("Array contains %d random numbers.\n", n);

		generate(n);

		struct data d[3];
		for (int i = 0; i < n; i++)
		{
			d[0].arr[i] = arrradix[i];
			d[1].arr[i] = arrradix[i];
			d[2].arr[i] = arrradix[i];
		}
		d[0].n = n;
		d[1].n = n;
		d[2].n = n;

		pthread_t tid[3];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		//-----------------------------------------------------------------------------------RADIX

		printf("-----------------------------------------------------------------------------------RADIX");
		t1 = clock();
		pthread_create(&tid[0], &attr, RadixSort, &d[0]);
		pthread_join(tid[0], NULL);
		t2 = clock();

		printf("\nRadix Sort: ");
		for (int i = 0; i < n; i++)
			printf("%d ", d[0].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

		//-----------------------------------------------------------------------------------BUBBLE

		printf("-----------------------------------------------------------------------------------BUBBLE");
		t1 = clock();
		pthread_create(&tid[1], &attr, BubbleSort, &d[1]);
		pthread_join(tid[1], NULL);
		t2 = clock();

		printf("\nBubble Sort: ");
		for (int i = 0; i < n; i++)
			printf("%d ", d[1].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

		//-----------------------------------------------------------------------------------INSERTION

		printf("-----------------------------------------------------------------------------------INSERTION");
		t1 = clock();
		pthread_create(&tid[2], &attr, InsertionSort, &d[2]);
		pthread_join(tid[2], NULL);
		t2 = clock();

		printf("\nInsertion Sort: ");
		for (int i = 0; i < n; i++)
			printf("%d ", d[2].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);
	}
}