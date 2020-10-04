#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#define maxcmd 20

char *argp[100];
int arglen;
char buf[100][100];
int buflen;

char PrevCmd[maxcmd][500];
int cmdno;

void GetArgs(char c[])
{
	int i=0;
	
	arglen = 0;
	
	buflen = 0;

	int eol = 0;
	
	while(eol == 0)
	{
		if(c[i] == '\0')
		{
			eol = 1;
			
			buf[arglen][buflen] = '\0';
				
			argp[arglen] = buf[arglen];
			arglen++;
			
			buflen = 0;
		}
		
		else 
		{
			if(c[i] == ' ')
			{
				buf[arglen][buflen] = '\0';
				
				argp[arglen] = buf[arglen];
				arglen++;

				buflen = 0;
			}
			
			else 
			{
				buf[arglen][buflen] = c[i];
				buflen++;
			}
		}
		
		i++;
	}
	
	argp[arglen] = NULL;
}

void DisplayHistory(int h)
{
	printf("\n");
	
	for(int i=0;i<h && i<maxcmd && cmdno > i;i++)
	{
		int j = (cmdno-1-i)%maxcmd;
		printf("%s\n", PrevCmd[j]);
	}
}

int main()
{
	char cmd[500];
	char cwd[128];
	cmdno = 0;
	printf("\nCOMMAND SHELL MOD\n\n1. Use 'exit' to kill the MOD shell\n2. Use '!x' to display first x history\n	*if x exceeds the present history limit it displays the complete history\n	**Max value of x is 20\n");
	printf("\n----------------------------------------------------------\n");
	
	while(1)
	{
		if(getcwd(cwd, sizeof(cwd))==NULL)
    	{
    		perror("getcwd() error");
    		return 1;
    	}
    	
        printf("\n");
        printf("\033[1;32m");
        printf("MOD:");
        printf("\033[0m");
        printf("\033[1;34m");
        printf("~%s",cwd);
        printf("\033[0m");
        printf("$ ");
        fflush(stdout);
        scanf("%[^\n]%*c", cmd);
       

		if(strcmp(cmd, "exit") == 0)
		{
			goto s;
		}
		
		else if(cmd[0] == '!')
		{
			int h;
			if (!cmd[2])
				h = (int)cmd[1] - 48;
			else
			{
				int x = (int)cmd[1] - 48;
				int y = (int)cmd[2] - 48;
				h = 10*x + y;
			}
			
			DisplayHistory(h);
		}
		
		else 
		{	
			int pid = vfork();
			
			if(pid == 0)
			{
				strcpy(PrevCmd[cmdno%maxcmd], cmd);
				cmdno++;
			
				GetArgs(cmd);
				printf("\n");
				if(execvp(argp[0], argp) == -1)
				{
					printf("%s: command not found.\n", argp[0]);
				}
				exit(0);
			}
			
			else 
			{
				wait(NULL);
			}
		}
	}
	s:	printf("\n----------------------------------------------------------\n");
	return 0;
}
