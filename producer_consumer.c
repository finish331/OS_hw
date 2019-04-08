#include<stdlib.h>
#include <stdio.h>
#include<pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE]
int counter = 0;
pthread_mutex_t mutex;
sem_t full, empty;

int main(int argc, char **argv){
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
}

int insert_item(buffer_item item){
    int success = 0;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    if(counter < BUFFER_SIZE){
        buffer[counter] = item;
        counter += 1;
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
        counter -= 1;
        success = 0;
    }
    else{
        success = -1;
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return success;
}

void *producer(void *param){
    buffer_item item;

}

void *consumer(void *param){
    buffer_item item;
}
