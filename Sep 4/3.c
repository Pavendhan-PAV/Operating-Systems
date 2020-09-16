#include <stdio.h> 
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<sys/wait.h>
#define lli long long int

lli sum=0;

int main() 
{ 
	lli x;
	
	printf("Enter the upper bound to list Armstrong numbers till this UB: ");
	scanf("%lld",&x);	
	
	int fd1[2]; //P->c
	int fd2[2]; //C->p
	
	if(pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		perror("\nPipe error!");
		return 1;
	}
	
	pid_t pid;
	pid = fork();

	if(pid > 0)
    {  
        close(fd1[0]);
        close(fd2[1]);
        printf("\n-----PARENT-----\n");
        printf("[+]Checking...\n");
       	printf("Armstrong numbers:");
       	
       	for(lli i=0; i<=x; i++)
       	{
       		write(fd1[1], &i, sizeof(i));
       		lli sum;
       		read(fd2[0], &sum, sizeof(sum));
       		
       		if(i == sum)
       			printf(" %lld",i);
       	}
        wait(NULL);
        printf("\n\n-----PARENT-----\n");
    }
	else if(pid== 0)
    {   
    	printf("\n-----CHILD-----\n");
    	 printf("[+]Calculating...\n");
       	close(fd1[1]);
        close(fd2[0]);
       	for(lli i=0; i<=x; i++)
       	{
       		lli num, temp;
       		read(fd1[0], &num, sizeof(num));
       		temp=num;
       		
       		lli order = (lli)floor(log10(num));
       		order++;
       		
       		lli sum=0;
       		while(num>0)
       		{
       			lli remainder = num%10;
       			sum+= (lli)pow(remainder,order);
       			num/=10;
       		}
       		
       		write(fd2[1], &sum, sizeof(sum));
       	}
       	printf("\n-----CHILD-----\n\n");
    }
    
    else{
    	printf("\nFork Error!");
    	exit(0);
    }
    	
	return 0; 
} 

