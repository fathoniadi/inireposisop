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
int execinput(char **, int);
int launchinputnormal(char **);
int launchinputdaemon(char **);
void signhndlr_c_z(int signalnum);



int main()
{
	char *input;
	char **args;
	int status=1;
	int daemon=0;
	int exit_eof=0;
	


	while(1)
	{
		signal(SIGTSTP,signhndlr_c_z);
		signal(SIGINT,signhndlr_c_z);
		input=insertinput(&daemon,&exit_eof);
		if(exit_eof==1) break;
		printf("daemon %d\n",daemon);
		args=splitinput(input);
		if(strcmp(args[0],"exit")==0) break;
		status=execinput(args,daemon);
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


int execinput(char **args, int daemon)
{
	int status;
	if(daemon==0) status=launchinputnormal(args);
	else; //status=launchinputdaemon(args);
}


int launchinputnormal(char **args)
{
	pid_t pid;
  	int status;

  	if(strcmp(args[0],"cd")==0)
	    {
	    	printf("a%sa\n",args[1]);
	    	printf("cd\n");
	    	chdir(args[1]);
	    }
	else
	{
		pid = fork();

	  if (pid == 0) {
	    // Child process
	    if (execvp(args[0], args) == -1) 
	    {
	      perror("lsh");
	    }
	    
	    exit(0);
	  } else if (pid < 0) {
	    // Error forking
	    //perror("lsh");
	  } else {
	    // Parent process
	    wait(0);
	  }
	}

	  return 1;
}
