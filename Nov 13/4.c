#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define SHARED 1

static int oxygen = 0, hydrogen = 0, count = 0, flag = 0;
sem_t mutex, hydro, oxy, barrier;

void bond()
{

    printf("[H2O] Molecules Bonded!!!\n");
    count += 1;

    if (count == 5)
    {
        printf("\n[ * ] Maximum Generated Water Molecules: %d\n\n", count);
        exit(1);
    }
    sleep(1);
}
void *hydrogen_thread()
{
    printf("[ H ] Hydrogen Molecule Generated: %ld\n", pthread_self());
    while (1)
    {
        sem_wait(&mutex);
        hydrogen += 1;
        if (hydrogen >= 2 && oxygen >= 1)
        {
            sem_post(&hydro);
            sem_post(&hydro);
            hydrogen -= 2;
            sem_post(&oxy);
            oxygen -= 1;
        }
        else
            sem_post(&mutex);

        sem_wait(&hydro);
        bond();

        sem_wait(&barrier);
    }
    pthread_exit(NULL);
}

void *oxygen_thread()
{
    printf("[ O ] Oxygen Molecule Generated: %ld\n", pthread_self());
    while (1)
    {
        sem_wait(&mutex);
        oxygen += 1;
        if (hydrogen >= 2)
        {
            sem_post(&hydro);
            sem_post(&hydro);
            hydrogen -= 2;
            sem_post(&oxy);
            oxygen -= 1;
        }
        else
            sem_post(&mutex);

        sem_wait(&oxy);
        bond();

        sem_wait(&barrier);
        sem_post(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    printf("\n");
    pthread_t hyd[10], ox[5];
    sem_init(&mutex, SHARED, 1);
    sem_init(&hydro, SHARED, 0);
    sem_init(&oxy, SHARED, 0);
    sem_init(&barrier, SHARED, 3);

    for (int i = 0; i < 10; i++)
        pthread_create(&hyd[i], NULL, hydrogen_thread, NULL);
    for (int i = 0; i < 5; i++)
        pthread_create(&ox[i], NULL, oxygen_thread, NULL);

    for (int i = 0; i < 10; i++)
        pthread_join(hyd[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(ox[i], NULL);

    printf("\n");
    return 0;
}