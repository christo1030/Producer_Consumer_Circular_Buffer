
#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

        char buffer[15];
        sem_t mutex;
        sem_t emp;
        sem_t full;
        pthread_t consumerThread;
        pthread_t producerThread;

void* consumer(){
int i=0;
char ch;
while(buffer[i] != '*'){
	sem_wait(&full);
	sem_wait(&mutex);


	//sleep(1);
	ch = buffer[i];
	if(i == 14)
		i=0;
	else
		i++;
    printf("%c", ch);
	sem_post(&mutex);
	sem_post(&emp);


	//printf("%c", ch);
}
}


void *producer(void *arg){
                       // printf("Producer_start \n");

                         int j= 0;

                        char newChar;
                        int i = 0;
                        FILE* fp;
                        fp= fopen("mytest.dat", "r");
                        while(fscanf(fp,"%c",&newChar) != EOF){

                        sem_wait(&emp);
                        sem_wait(&mutex);

                            //add the item to the  buffer
                         if(i >= 15){
                            i =0;
                            }
                        buffer[i]= newChar;
                        i++;

                        sem_post(&mutex);
                        sem_post(&full);
                        }

                        buffer[i]='*';

                      /*  for(j=0; j<i+1;j++){
                           printf("%c", buffer[j]);
                        }

                        */
}

main()
{
        int val =0;
        int err;
        sem_init(&mutex, 0, 1);
        sem_init(&emp, 0, 15);
        sem_init(&full, 0, 0);



        err = pthread_create(&(producerThread), NULL, &producer, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully1\n");

           err = pthread_create(&(consumerThread), NULL, &consumer, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully2\n");


pthread_join( producerThread,NULL);
pthread_join( consumerThread,NULL);

   }
