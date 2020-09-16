#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

void FibonacciNumbers(int n)  
{  
    int f1 = 0, f2 = 1, i;  
  
    if (n < 1)  
        return;  
  
    for (i = 1; i <= n; i++)  
    {  
        printf("%d ",f2); 
        int next = f1 + f2;  
        f1 = f2;  
        f2 = next;  
    }  
}  

void PrimeNumbers(int n)
{
   	int i = 3, count, c;
 
   	if ( n >= 1 )
      	printf("2 ");
 
   	for ( count = 2 ; count <= n ;  )
   	{
      	for ( c = 2 ; c <= i - 1 ; c++ )
      	{
        	 if ( i%c == 0 )
          	 break;
      	}
      	if ( c == i )
      	{
         	printf("%d ",i);
         	count++;
      	}
      	i++;
   	}	    
}     

int main()
{
	pid_t pid;
	int n;
	printf("Enter number of terms for fibonacci/prime series to be generated (natural numbers): ");
	scanf("%d",&n);

	pid=fork();
	if(pid)
    {  
        printf("\nParent - Fibonacci Series\n");
       	FibonacciNumbers(n);            
    }
	else
    {   
    	printf("\nChild - Prime Series\n");
        PrimeNumbers(n);
    }

	printf("\nChild pid: %d with Parent pid: %d\n",getpid(),getppid());

	return 0;	
}
