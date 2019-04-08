#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE]
int counter;
pthread_mutex_t mutex;
sem_t full, empty;

int insert_item(buffer_item item){
    int success = 0;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    if(counter < BUFFER_SIZE){
        buffer[counter] = item;
        counter++;
        success = 0;
    }
    else{
        success = -1;
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return success;
}

int remove_item(buffer_item *item){
    int success = 0;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    if(counter != 0){
        *item = buffer[counter];
        counter--;
        success = 0;
    }
    else{
        success = -1;
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return success;
}

void *producer(void *param) {
    buffer_item item;

    while (1) {
		/* sleep for a random period of time */
		sleep(rand());

		/* generate a random number */
		item = rand();
		if (insert_item(item))
			printf("report error condition");
		else
			printf("producer produced %d\n",item);
	}
}

void *consumer(void *param) {
    buffer_item item;

	while (1) {
		/* sleep for a random period of time */
		sleep(rand());

		if (remove_item(&item))
			printf("report error condition");
		else
			printf("consumer consumed %d\n",item);
	}
}

int main(int argc, char **argv){
    counter = 0;
    int i = 0;
    int sleepTime = atoi(argv[1]);
    int producerNumber = atoi(argv[2]);
    int consumerNumber = atoi(argv[3]);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    pthread_t producers[producerNumber];
    pthread_t consumers[consumerNumber];

    for(i = 0; i < producerNumber ; i++){
        pthread_creat(producers[i],NULL,producer,NULL);
    }
    for(i = 0; i < consumerNumber ; i++){
        pthread_creat(consumers[i],NULL,consumer,NULL);
    }
    sleep(sleepTime);
    return 0;
}
