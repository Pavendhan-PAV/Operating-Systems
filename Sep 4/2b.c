#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int n,i,sum=0;
	printf("Enter number of terms for odd/even series to be generated (natural numbers): ");
	scanf("%d",&n);

	pid=fork();
	if(pid)
    {  
    	i=0;
        printf("\nParent - Even Series\n");
        while (i<=n){ sum+=i;i+=2; }             
    	printf("Even Sum: %d \n",sum); 
    }
	else
    {   
    	printf("\nChild - Odd Series\n");
        i=1;
        while (i<=n) { sum+=i;i+=2;} 
        printf("Odd Sum: %d \n",sum); 
    }

	
	printf("Child pid: %d with Parent pid: %d\n",getpid(),getppid());

	return 0;	
}
