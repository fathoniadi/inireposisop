#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//int count=0;

typedef struct cekprima{
	int num;
	int count;
}cekprima;
void *prima(void *arg)
{
//	int t=*((int*)i);
//	free(i);
	cekprima *cek=(cekprima*)arg;
	//printf("%d\n",cek->num);	
	int k,counter;
	counter=0;
	for(k=1;k<=cek->num;k++)
		{
			if(cek->num % k==0)counter++;
		}
	cek->count=0;
	if(counter==2)
	{	
		cek->count++;
		printf("%d %d\n",cek->num, cek->count);
	}
}

int main()
{

	int i,j,c=0,z;
	scanf("%d", &z);
	cekprima cek[z];
	pthread_t thread[z];
	//cek.count=0;
	for(i=1;i<=z;i++){
		//cekprima *cek=malloc(sizeof(*cek));		
		cek[i].num=i;
		pthread_create(&thread[i],NULL,prima,(void*)&cek[i]);	
	}
	for(i=1;i<=z;i++){
		pthread_join(thread[i],NULL);
		c=c+cek[i].count;
	}
	printf("%d\n",c);

}
