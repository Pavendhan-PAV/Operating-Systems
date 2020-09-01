#include<stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    pid=fork(); //A
    
    if (pid<0) fprintf(stderr,"Failed fork \n");
    else if (pid==0)
    {
        fork(); //B
        printf("Child print \n");
    }
    else if (pid>0)
        printf("Parent Print \n");
    
    printf("Main Print \n\n");
    return 0;
}