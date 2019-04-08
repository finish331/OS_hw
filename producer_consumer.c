#include<stdlib.h>
#include <stdio.h>
#include<pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE]
pthread_mutex_t mutex;
sem_t full, empty;

int main(int argc, char **argv){

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
}

int insert_item(buffer_item item){

}

int remove-item(buffer_item *item){

}

void *producer(void *param){
    buffer_item item;
}

void *consumer(void *param){
    buffer_item item;
}
