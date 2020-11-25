#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (pNum + 4) % N
#define RIGHT (pNum + 1) % N

int state[N];
int Philosophers[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(int pNum)
{
	if (state[pNum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	{
		// eating state
		state[pNum] = EATING;

		sleep(2);
		printf("[ + ] Philosopher %d takes chopsticks %d and %d\n", pNum + 1, LEFT + 1, pNum + 1);
		printf("[+++] Philosopher %d is Eating\n", pNum + 1);

		// triggers hungry philosophers during putfork
		sem_post(&S[pNum]);
	}
}

void take_fork(int pNum)
{
	sem_wait(&mutex);

	// hungry state
	state[pNum] = HUNGRY;
	printf("[ * ] Philosopher %d is Hungry\n", pNum + 1);

	// check neighbours state
	test(pNum);
	sem_post(&mutex);
	// if unable to eat wait to be signalled depending upon neighbours state
	sem_wait(&S[pNum]);

	sleep(1);
}

void put_fork(int pNum)
{
	sem_wait(&mutex);

	// thinking state
	state[pNum] = THINKING;

	printf("[ - ] Philosopher %d putting chopsticks %d and %d down\n",
		   pNum + 1, LEFT + 1, pNum + 1);
	printf("[...] Philosopher %d is thinking\n", pNum + 1);

	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void *philospher(void *num)
{

	while (1)
	{
		int *i = num;

		sleep(1);
		take_fork(*i);
		sleep(0);

		put_fork(*i);
	}
}

int main()
{
	printf("\n");
	int i;
	pthread_t thread_id[N];
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)
		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++)
	{
		pthread_create(&thread_id[i], NULL, philospher, &Philosophers[i]);
		printf("[...] Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);
}
