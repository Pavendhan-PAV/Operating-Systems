#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int n,i;
	printf("Enter number of terms for odd/even series to be generated (natural numbers): ");
	scanf("%d",&n);

	pid=fork();
	if(pid)
    {  
    	i=2;
        printf("\nParent - Even Series\n");
        while (i<=n){ printf("%d ",i);i+=2; }             
    }
	else
    {   
    	printf("\nChild - Odd Series\n");
        i=1;
        while (i<=n) { printf("%d ",i);i+=2;} 
    }

	printf("\nChild pid: %d with Parent pid: %d\n",getpid(),getppid());

	return 0;	
}
