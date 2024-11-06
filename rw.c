#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t mutex,wr;
int a=10;
int readcount=0;
void * writer(void * arg)
{
   
    long int num=(long int )arg;
    
        pthread_mutex_lock(&wr);
        printf("\n writer %ld is in critical section",num);
        printf("\n writer %ld have writtern data as %d",num,++a);
        sleep(1);
        
        pthread_mutex_unlock(&wr);
        printf("\n writer %ld has left the critical section",num);
   
}
void * reader(void * arg)
{
    long int num=(long int )arg;
    
        pthread_mutex_lock(&mutex);
        readcount++;
        pthread_mutex_unlock(&mutex);
        
        if(readcount==1)
        {
            pthread_mutex_lock(&wr);
        }
        printf("\n reader %ld is in critical section",num);
        printf("\n reader %ld have read data as %d",num,a);
        sleep(1);
        pthread_mutex_lock(&mutex);
        readcount--;
        pthread_mutex_unlock(&mutex);
        
        if(readcount==0)
        {
            pthread_mutex_unlock(&wr);
        }
        
        printf("\n reader %ld has left the critical section",num);
   
}
int main()
{
    pthread_t r[10],w[10];
    int nor,now;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&wr,NULL);
    
    printf("enter no of reader and writers");
    scanf("%d%d",&nor,&now);
    
    int i,j,k,l;
    
    for(i=0;i<nor;i++)
    {
        pthread_create(&r[i], NULL, reader, (void *)i);
    }
    
    for(j=0;j<now;j++)
    {
        pthread_create(&w[j], NULL, writer, (void *)j);
    }
    
    for(k=0;k<nor;k++)
    {
        pthread_join(r[k],NULL);
    }
    
    for(l=0;l<now;l++)
    {
        pthread_join(w[l],NULL);
    }
}
