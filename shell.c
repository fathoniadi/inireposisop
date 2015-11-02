#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#define STR_DELIMS "\t\r\n\a "
#define CHAR_SIZE 1024
#define STR_SIZE 64


char *insertinput(int *);
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
	int daemon;
	


	while(1)
	{
		signal(SIGQ,signhndlr_c_z);
		signal(SIGINT,signhndlr_c_z);
		input=insertinput(&daemon);
		args=splitinput(input);
		printf("%d\n",daemon);
		if(strcmp(args[0],"exit")==0) break;
		status=execinput(args,daemon);
		free(input);
		free(args);
		daemon=0;
	}

	return EXIT_SUCCESS;
}

void signhndlr_c_z(int signalnum)
{
	
}

char * insertinput(int *daemon)
{
	char a;
	int counter=0;
	int charsize=CHAR_SIZE;
	char *character=malloc(sizeof(char)*CHAR_SIZE);
	printf("E03Shell > ");
	while(1)
	{
		scanf("%c",&a);
		if(a==EOF) printf("aaaa\n");
		if(a=='&') *daemon=1; 
		if(a=='\n')
		{
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
	//return character;
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
	pid_t pid, wpid;
  int status;

  pid = fork();

  if (pid == 0) {
    // Child process
    int a=(int)wpid;
    printf("Status %d\n",a);
    //if(strcmp(args[0],"cd")==0)
    /*if (execvp(arg[0], args) == -1) {
      perror("lsh");
    }*/
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    
    exit(0);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    wait(0);
  }

  return 1;
}