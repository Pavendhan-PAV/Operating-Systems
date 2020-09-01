#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main ()
{
	printf("Process 1 - PARENT\n");
	pid_t C_2, C_3;
	C_2 = fork(); //--------------------------------------1 forks 2

	if (C_2 == 0)
	{
		//CHILD 2
		printf("C_2\n");
		pid_t C_4, C_5, C_6;
		C_4=fork(); //------------------------------------2 forks 4

		if(C_4==0)
		{
			//CHILD 4
			printf("C_4\n");
			pid_t C_8 =fork(); //-------------------------4 forks 8

			if(C_8==0)
				printf("C_8\n"); //child 8 code
		}
		
		else
		{
			C_5=fork(); //--------------------------------2 forks 5
			if(C_5==0)
			{
				//CHILD 5
				printf("C_5\n");
				pid_t C_9=fork(); //----------------------5 forks 9

				if(C_9==0)
					printf("C_9\n"); //CHILD 9
			}

			else
			{
				C_6=fork(); //----------------------------2 forks 6
				if(C_6==0)
					printf("C_6\n"); //CHILD 6
			}
		}
	}

	else
	{
		C_3 = fork(); //----------------------------------1 forks 3
		if (C_3 == 0)
		{
			//CHILD 3
			printf("C_3\n");
			pid_t C_7;
			
			C_7=fork(); //--------------------------------3 forks 7
			if(C_7==0)
				printf("C_7\n"); //CHILD 7
		}
	}

	return 0;
}				
