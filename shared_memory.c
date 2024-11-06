//writer
/*#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    key_t key=ftok("shmfile",65);
    
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    
    char * str=(char *) shmat(shmid,(void *)0,0);
    
    printf("\n write data : ");
    gets(str);
    
    printf("\n data written in memory: %s ",str);
    
    shmdt(str);
    
    return 0;
}*/
//reader
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    key_t key=ftok("shmfile",65);
    
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    
    char * str=(char *)shmat(shmid,(void *)0,0);
    
    printf("\n data reda from memory : %s",str);
    
    shmdt(str);
    
    shmctl(shmid,IPC_RMID,NULL);
    
    return 0;
}

