#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

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
	//count=0;
	cek->count=0;
	if(counter==2)
	{	
		printf("%d ",cek->num);
		cek->count++;
		//printf("%d %d\n",cek->num, cek->count);
	}
}

int main()
{

	int i,j,c=0,testcase;
	printf("Masukkan batas :");
	scanf("%d", &testcase);
	cekprima *cek=malloc(sizeof(*cek)*(testcase+1));
	pthread_t *thread=malloc(sizeof(pthread_t)*(testcase+1));
	//cek.count=0;
	for(i=1;i<=testcase;i++){
				
		cek[i].num=i;
		pthread_create(&thread[i],NULL,prima,(void*)&cek[i]);
		//printf("%d",cek[i].count);
		//membuat thread baru sejumlah N	
	}
	for(i=1;i<=testcase;i++){
		pthread_join(thread[i],NULL);
		c+=cek[i].count;
		//c+=cek[i].count;
		
	}
	printf("\nJumlah Bilangan Prima sampai angka %d adalah %d\n",testcase,c);//mencetak jumlah bilangan prima sampai dengan N/testcase
	free(cek);
	free(thread);

}
