#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int fib(int n)
{
	if (n==0)
		return 0;
	else if(n==1)
		return 1;
	else
	{
		int x=0;
		pid_t pid;
		pid=vfork(); 	
		
		if(pid==0) //CHILD BLOCK
		{
			x+=fib(n-1);
			_exit(0);
		}
		else //PARENT BLOCK
		{
			wait(NULL);
			x+=fib(n-2);
			return x;
		}
	}
}

int main()
{
	int n;
	printf("Enter number for n Fibonacci series generation: ");
	scanf("%d",&n);

	printf("\n-----FIBONACCI SERIES-----\n");

	for(int i=0;i<=n;i++)
		printf("%d ",fib(i));
	printf("\n");
	return 0;
} 
