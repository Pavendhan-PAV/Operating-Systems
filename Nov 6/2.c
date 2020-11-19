#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SHARED 1

int data;
int flag[2];
int turn;

sem_t empty, full;

void lock_ini()
{
	flag[0] = 0;
	flag[1] = 0;
	turn = 0;
}

void lock(int index)
{
	flag[index] = 1;
	turn = 1 - index;
	while (flag[1 - index] == 1 && turn == 1 - index)
		;
}

void unlock(int index)
{
	flag[index] = 0;
}

void *producer()
{
	int p_no;
	//printf("\033[1;31m");
	printf("\nNEW PRODUCER ID: %ld\n\n", pthread_self()); //print thread id

	for (p_no = 1; p_no < 6; p_no++)
	{
		sem_wait(&empty);
		//entry-section
		lock(0);
		//cs start
		//assume data to the new producer no
		data = p_no;
		//cs end
		unlock(0);
		//exit section
		sem_post(&full);
		//printf("\033[1;31m"); //Display in red
		printf("[+]Produced Data: %d\n", data);
	}
}
void *consumer()
{
	int c_no, total = 0;
	//printf("\033[1;33m");
	printf("\nNEW CONSUMER ID: %ld\n\n", pthread_self());
	for (c_no = 1; c_no < 6; c_no++)
	{
		sem_wait(&full);
		//entry-section
		lock(1);
		//cs start
		total = total + data;
		//cs end
		unlock(1);
		//exit section
		sem_post(&empty);
		//printf("\033[1;33m"); //Display in yellow
		printf("[-]Consumed Data: %d\n", data);
	}
	printf("\nTOTAL CONSUMED DATA: %d\n", total);
}

//empty to check whether buffer is empty;default 1
//full to check whether buffer is full;default 0
//lock is mutext lock;default 1

int main()
{
	pthread_t p1, c1;
	lock_ini();
	sem_init(&empty, SHARED, 1);
	sem_init(&full, SHARED, 0);

	pthread_create(&p1, NULL, producer, NULL);
	pthread_create(&c1, NULL, consumer, NULL);

	pthread_join(p1, NULL);
	pthread_join(c1, NULL);

	printf("\n[-]Simulation Aborted!\n\n");
}