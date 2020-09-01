#include<stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    pid=fork(); //A
    
    if (pid>0) {
        fork(); //B
        printf("OS\n");
    }
        
    printf("Hello \n\n");
    return 0;
}