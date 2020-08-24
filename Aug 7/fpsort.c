#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int asc(int a, int b)
{
    return a > b;
}

int desc(int a, int b)
{
    return b > a;
}

void bubblesort(int arr[], int size, int (*compare)(int a, int b))
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size-1;j++)
		{
			if((*compare)(arr[j],arr[j+1]))
 			{
  		 		int t=arr[j];
  		 		//printf("%d",t);
   				arr[j]=arr[j+1];
				arr[j+1]=t;
  			}
		}
	}
	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
}

int main(int argc, char** argv)
{
	if (argc <= 2)
    {
        printf("syntax: ./fsort <size> <0-des/1-asc> <integers>\n");
        return EXIT_FAILURE;
    }
    
	int size=((int)*argv[1] - 48);
	
	if(size != argc-3)
	{
		printf("Number of arguments mismatch! Aborting.\n");
		return 0;
	}
	
	int choice=((int)*argv[2] - 48);
	
	int arr[size];
    for (int i = 0; i < size; i++)
        arr[i] = ((int)*argv[i+3] -48);
	
	switch(choice)
	{
		case 0: 
			printf("DESCENDING ORDER: ");
			bubblesort(arr, size, desc);
			printf("\n");
			break;
			
		case 1:
			printf("ASCENDING ORDER: ");
			bubblesort(arr, size, asc);
			printf("\n");
			break;
		
		default: 
			printf("\nNO SUCH CASE");
			printf("\n");
			break;
			
			
			
	}
	return EXIT_SUCCESS;
}
