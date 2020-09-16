#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int asc(const void * p1, const void * p2)
{
    return (*(int*)p1 - *(int*)p2);
}

int desc(const void * p1, const void * p2)
{
   return (*(int*)p2 - *(int*)p1);
}

int main()
{
	pid_t pid;
	int n;
	printf("Enter number of terms for Asc/Desc sort to be generated (natural numbers): ");
	scanf("%d",&n);

	int a[n];
	printf("\nEnter the %d elements: ",n);
	for(int i=0; i<n; i++)
		scanf("%d",&a[i]);
	
	pid=fork();
	if(pid)
    {  
        printf("\nParent - Asc Sort\n");
        qsort(a, n, sizeof(int), asc);
        for(int i=0; i<n; i++)
		printf("%d ",a[i]);
    }
	else
    {   
    	printf("\nChild - Desc Sort\n");
        qsort(a, n, sizeof(int), desc);
        for(int i=0; i<n; i++)
		printf("%d ",a[i]);
    }

	
	printf("\n	Child pid: %d with Parent pid: %d\n",getpid(),getppid());

	return 0;	
}
