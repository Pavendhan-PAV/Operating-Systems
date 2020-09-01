#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();

    if (pid < 0)
        printf("Failed\n");

    else if (pid == 0)
        printf("Child\n");
    
    else
        printf("Parent\n");
    
    printf("Hello!\n");

    return 0;
}