#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define SHARED 1

int elvesCount = 0;
int reindeerCount = 0;
sem_t santa_s, reindeer_s, elf_s, mutex;

void prepare()
{
    printf("[* *] Sleigh is being Prepared!!!\n");
}

void gethitched(long int val)
{
    printf("[***] Reindeer being hitched!!! ID: %ld \n", val);
    sleep(1);
}

void gethelp()
{
    sleep(1);
    if (elvesCount == 1)
        printf("\n[ - ] Elf waiting for help!!!\n");
    else
    {

        printf("[ - ] Elf waiting for help!!!\n");
    }
    sleep(1);
}

void helpElves()
{
    printf("[+++] Santa Helped Elves and toys are made!!!\n\n");
}

void *santa()
{
    while (1)
    {
        sem_wait(&santa_s);
        sem_wait(&mutex);
        if (reindeerCount == 9)
        {
            printf("\n[ * ] Santa Woke Up!!! ID: %ld\n", pthread_self());
            prepare();
            reindeerCount = 0;

            for (int j = 0; j < 9; j++)
                sem_post(&reindeer_s);
        }
        else if (elvesCount == 3)
        {
            sleep(1);
            printf("[---] Elves having difficulty to build toys!!!\n");
            printf("[ + ] Santa Woke Up!!! ID: %ld\n", pthread_self());
            helpElves();
        }
        sem_post(&mutex);
    }
}

void *reindeer()
{
    printf("[ - ] Reindeer Back from Vacation!!! ID: %ld\n", pthread_self());
    while (1)
    {
        sem_wait(&mutex);
        reindeerCount += 1;
        if (reindeerCount == 9)
            sem_post(&santa_s);
        sem_post(&mutex);

        sem_wait(&reindeer_s);
        gethitched(pthread_self());
    }
}

void *elves()
{
    while (1)
    {
        sem_wait(&elf_s);
        sem_wait(&mutex);
        elvesCount += 1;
        int flag = 0;
        if (elvesCount == 3)
        {
            sem_post(&santa_s);
            flag = 1;
        }
        else

            sem_post(&elf_s);
        //if (flag == 1)
        //             printf("\n[ - ] Elves having difficulty to build toys!!!\n");
        sem_post(&mutex);
        gethelp(elvesCount);

        sem_wait(&mutex);

        elvesCount -= 1;
        if (elvesCount == 0)
            sem_post(&elf_s);
        sem_post(&mutex);
    }
}

int main()
{
    printf("\n");

    pthread_t san, elv[3], rend[9];
    sem_init(&santa_s, SHARED, 0);
    sem_init(&reindeer_s, SHARED, 0);
    sem_init(&elf_s, SHARED, 1);
    sem_init(&mutex, SHARED, 1);

    pthread_create(&san, NULL, santa, NULL);
    for (int i = 0; i < 9; i++)
        pthread_create(&rend[i], NULL, reindeer, NULL);
    for (int i = 0; i < 3; i++)
        pthread_create(&elv[i], NULL, elves, NULL);

    pthread_join(san, NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(elv[i], NULL);
    for (int i = 0; i < 9; i++)
        pthread_join(rend[i], NULL);

    printf("\n");
    return 0;
}