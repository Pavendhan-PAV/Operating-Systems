#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv)
{
	if (argc <= 3)
    {
        printf("syntax: ./sort <size> <0-des/1-asc> [<integers>/<decimals>/<strings>]\n");
        return EXIT_FAILURE;
    }
	int n=((int)*argv[1] - 48)+3;
	//printf("%d",n);
	
	if(n != argc)
	{
		printf("Number of arguments mismatch! Aborting.\n");
		return 0;
	}
	
	int choice=((int)*argv[2] - 48);
	
	switch(choice)
	{
		case 0: 
			printf("DESCENDING ORDER: ");
			for(int i=3;i<n;i++)
			{
				for(int j=3;j<n-1;j++)
				{
					//printf("%dhjjjjj",(int)*argv[j+1]-48);
					if((int)*argv[j]<(int)*argv[j+1])
  					{
  			 			int t=((int)*argv[j]-48);
  			 			//printf("%d",t);
   						*argv[j]=((int)*argv[j+1]);
						*argv[j+1]=t+48;
  					}
				}
			}
			for(int i=3;i<n;i++)
				printf("%d ",((int)*argv[i])-48);
				
			printf("\n");
			break;
			
		case 1:
			printf("ASCENDING ORDER: ");
			for(int i=3;i<n;i++)
				for(int j=3;j<n-1;j++)
				{
					if((int)*argv[j]>(int)*argv[j+1])
  					{
  			 			int t=((int)*argv[j]-48);
  			 			//printf("%d",t);
   						*argv[j]=((int)*argv[j+1]);
						*argv[j+1]=t+48;
  					}
				}
			for(int i=3;i<n;i++)
				printf("%d ",((int)*argv[i])-48);
			printf("\n");
			break;
		
		default: 
			printf("\nNO SUCH CASE");
			break;
	}
}
