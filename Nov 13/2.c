#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define READ_COUNT 3
#define WRITE_COUNT 5

sem_t wrt;
pthread_mutex_t mutex;
int count = 1;
int numreader = 0;

void *writer(void *wno)
{
	sem_wait(&wrt);
	count = count * 2;
	printf("[+] Writer %d: Wrote count to %d\n", (*((int *)wno)), count);
	sem_post(&wrt);
}

void *reader(void *rno)
{
	pthread_mutex_lock(&mutex);
	numreader++;
	if (numreader == 1)
	{
		sem_wait(&wrt); // If this id the first reader, then it will block the writer
	}
	pthread_mutex_unlock(&mutex);
	printf("[-] Reader %d: Read count as %d\n", *((int *)rno), count);

	pthread_mutex_lock(&mutex);
	numreader--;
	if (numreader == 0)
	{
		sem_post(&wrt); // If this is the last reader, it will wake up the writer.
	}
	pthread_mutex_unlock(&mutex);
}

int main()
{
	printf("\n");
	pthread_t read[READ_COUNT], write[WRITE_COUNT];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&wrt, 0, 1);

	int readers[READ_COUNT];
	for (int i = 0; i < READ_COUNT; i++)
		readers[i] = i + 1;

	int writers[WRITE_COUNT];
	for (int i = 0; i < WRITE_COUNT; i++)
		writers[i] = i + 1;

	for (int i = 0; i < WRITE_COUNT; i++)
		pthread_create(&write[i], NULL, (void *)writer, (void *)&writers[i]);

	for (int i = 0; i < READ_COUNT; i++)
		pthread_create(&read[i], NULL, (void *)reader, (void *)&readers[i]);

	for (int i = 0; i < READ_COUNT; i++)
		pthread_join(read[i], NULL);

	for (int i = 0; i < WRITE_COUNT; i++)
		pthread_join(write[i], NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);

	printf("\n");
	return 0;
}