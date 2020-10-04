#include<stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h>
 
int main() 
{ 
	long int count=0;
	int n=900000;
	
	for(int i=0; i<n; i++)
	{
		if(fork()==0)
			exit(1);
	}	
	
	for(int i=0; i<n; i++)
	{
		int pid;
		wait(&pid);
		pid /= 255; //the wait catches the child process's exit status 255 times
		count+=pid; 
	}
			
	printf("Maximum fork count: %ld\n",count);

	return 0; 
} 

