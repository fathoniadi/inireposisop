#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//int count=0;

typedef struct cekprima{
	int num;//angka yang sedang di cek
	int count;//sebagai penanda bilangan prima ata bukan
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
		//printf("%d %d\n",cek->num, cek->count);
	}
}

int main()
{

	int i,j,c=0,testcase;
	printf("Masukkan batas :");
	scanf("%d", &testcase);
	cekprima cek[testcase];
	pthread_t thread[testcase];
	//cek.count=0;
	for(i=1;i<=testcase;i++){
		//cekprima *cek=malloc(sizeof(*cek));		
		cek[i].num=i;
		pthread_create(&thread[i],NULL,prima,(void*)&cek[i]);//membuat thread baru sejumlah N	
	}
	for(i=1;i<=testcase;i++){
		pthread_join(thread[i],NULL);
		c=c+cek[i].count;
	}
	printf("Jumlah Bilangan Prima sampai angka %d adalah %d\n",testcase,c);//mencetak jumlah bilangan prima sampai dengan N/testcase

}
