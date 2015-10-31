#include <stdio.h>
#include <string.h>
#include <pthread.h>
FILE *inp, *cad;

typedef struct Name_file
{
	char file[100];
	char file_backup[100];
}Name_file;

void *copyfile(void *args)
{
	char ch;
	Name_file *name_file=(Name_file*) args;
	inp=fopen(name_file->file,"r");
	cad=fopen(name_file->file_backup,"w");

	printf("%s %s\n",name_file->file,name_file->file_backup);

	for(ch = getc(inp);ch!=EOF;ch=getc(inp))
	{
		putc(ch,cad);
	}
	fclose(inp);
	fclose(cad);
}

int main()
{
	pthread_t thread1, thread2;
	Name_file name_file[3];
	
	printf("Masukkan nama file > ");
	scanf("%s",name_file[0].file);

	strcpy(name_file[1].file,name_file[0].file);
	strcpy(name_file[0].file_backup,name_file[0].file);
	strcpy(name_file[1].file_backup,name_file[0].file);
	strcat(name_file[0].file_backup,".backup1");
	strcat(name_file[1].file,".backup1");
	strcat(name_file[1].file_backup,".backup2");
	
	pthread_create(&thread1,NULL,copyfile,(void *)&name_file[0]);	
	pthread_join(thread1,NULL);
	pthread_create(&thread2,NULL,copyfile,(void *)&name_file[1]);
	pthread_join(thread2,NULL);	
	
}