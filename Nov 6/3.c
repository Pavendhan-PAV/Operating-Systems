#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#define SHARED 1

//pete algo vars
int flag[2];
int turn;

//sem vars for buffer
sem_t empty, full;

//dict vars
char word[100][1000];
char primary[100][1000];
char secondary[100][1000];
char word_s[1000];
int size;

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

void create_dict()
{
    FILE *fp = fopen("words.txt", "r");
    char c = fgetc(fp);
    //while(c!=feof(fp))
    for (int i = 0; i < size; i++)
    {
        memset(word[i], 0, sizeof(word[i]));
        memset(primary[i], 0, sizeof(primary[i]));
        memset(secondary[i], 0, sizeof(secondary[i]));

        int index = 0;
        while (c != ';')
        {
            word[i][index++] = c;
            c = fgetc(fp);
        }
        index = 0;
        c = fgetc(fp);
        while (c != ';')
        {
            primary[i][index++] = c;
            c = fgetc(fp);
        }
        index = 0;
        c = getc(fp);
        while (c != '$')
        {
            secondary[i][index++] = c;
            c = fgetc(fp);
        }
        for (int j = 0; j < 2; j++)
            c = fgetc(fp);
    }

    fclose(fp);
}

void *producer()
{
    // printf("\033[1;31m");
    printf("\n[+]New Producer id :%ld\n", pthread_self()); //print thread id

    sem_wait(&empty);
    //entry-section
    lock(0);
    //cs start
    //assume data to the new producer no
    create_dict();
    //cs end
    unlock(0);
    //exit section
    sem_post(&full);
}
void search()
{
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word[i], word_s) == 0)
        {
            printf("\nWord Found By the Consumer -----\n\nWord:\t\t\t%s\nPrimary Meaning:\t%s.\nSecondary Meaning:\t%s.\n\n", word[i], primary[i], secondary[i]);
            flag = 1;
        }
    }
    if (flag == 0)
        printf("\nWord Not found By the Consumer as its not in the Dictionary!!!\n\n");
}
void *consumer()
{
    //printf("\033[1;33m");
    printf("[+]New Consumer id : %ld\n", pthread_self());

    sem_wait(&full);
    //entry-section
    lock(1);
    //cs start
    search();
    //cs end
    unlock(1);
    //exit section
    sem_post(&empty);
}

void findsize()
{
    FILE *fp = fopen("words.txt", "r");
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            size += 1;
    fclose(fp);
}

//empty to check whether buffer is empty;default 1
//full to check whether buffer is full;default 0
//lock is mutext lock;default 1

int main()
{
    findsize();
    int choice = 1;
    while (choice == 1)
    {
        printf("\nEnter the word to be searched for in the Dictionary: ");
        scanf("%s", word_s);

        pthread_t p1, c1;
        lock_ini();
        sem_init(&empty, SHARED, 1);
        sem_init(&full, SHARED, 0);

        pthread_create(&p1, NULL, producer, NULL);
        pthread_create(&c1, NULL, consumer, NULL);

        pthread_join(p1, NULL);
        pthread_join(c1, NULL);

        printf("Wish to search more? (0/1): ");
        scanf("%d", &choice);
    }
    printf("\n[-]Simulation Aborted!\n\n");
}