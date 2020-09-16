#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int occ[500];

int asc(const void * p1, const void * p2)
{
    return (*(int*)p1 - *(int*)p2);
}

int desc(const void * p1, const void * p2)
{
   return (*(int*)p2 - *(int*)p1);
}

int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r < l) 
        return -1; 
  
    int mid = l + (r - l) / 2; 
  
    if (arr[mid] == x) 
        return mid; 
    if (arr[mid] > x) 
        return binarySearch(arr, l, mid - 1, x); 

    return binarySearch(arr, mid + 1, r, x); 
} 
  
int Occurrences(int arr[], int n, int x) 
{ 
    int ind = binarySearch(arr, 0, n - 1, x); 
  
    if (ind == -1)
    { 
     	printf("\nOccurrences of %d in the array(indices): NO OCCURRENCE",x);
        return 0; 
  	}
  	
  	int k=0;
  	occ[k++]=ind+1;
  	
    int count = 1; 
    int left = ind - 1; 
    while (left >= 0 && arr[left] == x)
    { 
        occ[k++]=left+1;
        count++, left--; 
  	}
    int right = ind + 1; 
    while (right < n && arr[right] == x) 
   	{
   		occ[k++]=right+1;
        count++, right++; 
  	}
  	
  	qsort(occ, k, sizeof(int), asc);
  	printf("\nOccurrences of %d in the array(indices): ",x);
  	for(int i=0; i<k; i++)
		printf("%d ",occ[i]);
  	
    return count; 
} 

int main()
{
	pid_t pid;
	int n;
	printf("Enter number of terms for multiprocessing version of binary search (natural numbers): ");
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
		
	int x;
	printf("Enter the number to be searched for: ");
	scanf("%d",&x);
	
	pid=fork();
	if(pid)
    {  
        printf("\nParent - First half BS---\n");
        qsort(a, k, sizeof(int), asc);
        printf("Sorted array: ");
        for(int i=0; i<k; i++)
		printf("%d ",a[i]);
		int count = Occurrences(a,k,x);
		printf("\nTotal count: %d",count);
    }
	else
    {   
    	printf("\nChild - Other half BS---\n");
        qsort(b, j, sizeof(int), asc);
        printf("Sorted array: ");
        for(int i=0; i<j; i++)
		printf("%d ",b[i]);
		int count = Occurrences(b,j,x);
		printf("\nTotal count: %d",count);
    }

	
	printf("\n(Child pid: %d with Parent pid: %d)\n",getpid(),getppid());

	return 0;	
}
