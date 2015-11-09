#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#define STR_DELIMS "\t\r\n\a "
#define CHAR_SIZE 1024
#define STR_SIZE 64


char *insertinput(int *, int *);
char **splitinput(char *);
void execinput(char **, int);
void launchinputnormal(char **);
void launchinputdaemon(char **);
void signhndlr_c_z(int signalnum);



int main()
{
	char *input;
	char **args;
	int daemon=0;
	int exit_eof=0;
	


	while(1)
	{
		signal(SIGTSTP,signhndlr_c_z);
		signal(SIGINT,signhndlr_c_z);
		input=insertinput(&daemon,&exit_eof);
		if(exit_eof==1) break;
		args=splitinput(input);
		if(strcmp(args[0],"exit")==0) break;
		execinput(args,daemon);
		free(input);
		free(args);
		daemon=0;
		exit_eof=0;
	}

	return EXIT_SUCCESS;
}

void signhndlr_c_z(int signalnum)
{
	
}

char * insertinput(int *daemon, int *exit_eof)
{
	char a;
	int counter=0;
	int charsize=CHAR_SIZE;
	char *character=malloc(sizeof(char)*CHAR_SIZE);
	printf("E03Shell > ");
	int flag=1;
	while(1)
	{
		a=getchar();
		if(a==EOF) 
		{
			*exit_eof=1;
			break; 
		}
		if(a=='\n')
		{
			if(character[counter-1]=='&') *daemon=1;
			if(flag==1) 
			{
				printf("E03Shell > ");
				continue;
			}
			character[counter]='\0';
			return character;
		}
		else
		{
			character[counter]=a;
		}
		counter++;

		if(counter>=CHAR_SIZE)
		{
			charsize+=CHAR_SIZE;
			character=realloc(character, charsize);
		}
		flag=0;
	}
}

char **splitinput(char *input)
{
	int strsize=STR_SIZE;
	char **tokens=malloc(sizeof(char*)*strsize);
	char *token;
	int counter=0;

	token=strtok(input, STR_DELIMS);
	
	while(token!=NULL)
	{
		tokens[counter]=token;
		counter++;

		if(counter>=strsize)
		{
			strsize+=STR_SIZE;
			tokens=realloc(tokens, strsize * sizeof(char*));
		}
		token=strtok(NULL,STR_DELIMS);
	}
	tokens[counter]=NULL;
	return tokens;
}

void execinput(char **args, int daemon)
{
	int status;
	if(daemon==0) launchinputnormal(args);
	else; //status=launchinputdaemon(args);
}


void launchinputnormal(char **args)
{
	pid_t pid;
  	int status;

  	if(strcmp(args[0],"cd")==0)
	    {
	    	if(chdir(args[1])!=0) 
	    	{
	    		printf("E03: cd: %s: No such file or directory\n",args[1]);
	    	}
	    }
	else
	{
		pid = fork();

	  	if (pid == 0) 
	  	{
		    if (execvp(args[0], args) == -1) 
		    {
		      printf("%s: command not found\n",args[0]);
		    }
	    	exit(0);
	  	} 
	  	else if (pid < 0) 
	  	{
	    	perror("E03");
	  	} 
	  	else 
	  	{
	    	wait(0);
	  	}
	}

}
