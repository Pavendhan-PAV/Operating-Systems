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
	printf("Enter number of terms for Asc(1st half)/Desc(2nd half) sort to be generated (natural numbers): ");
	scanf("%d",&n);

	int arr[n];
	printf("\nEnter the %d elements: ",n);
	for(int i=0; i<n; i++)
		scanf("%d",&arr[i]);
		
	int i=0,j=0,k=0,a[n],b[n];
	for(i=0; i<n/2; i++)
		a[k++]=arr[i];
	for(; i<n; i++)
		b[j++]=arr[i];	
	
	pid=fork();
	if(pid)
    {  
        printf("\nParent - Asc Sort\n");
        qsort(a, k, sizeof(int), asc);
        for(int i=0; i<k; i++)
		printf("%d ",a[i]);
    }
	else
    {   
    	printf("\nChild - Desc Sort\n");
        qsort(b, j, sizeof(int), desc);
        for(int i=0; i<j; i++)
		printf("%d ",b[i]);
    }

	
	printf("\nChild pid: %d with Parent pid: %d\n",getpid(),getppid());

	return 0;	
}
