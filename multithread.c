#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double avg;
int min;
int max;

void *Compute_Avg(void *ptr){
    int *input = (int *) ptr;
    double total;
    int i = 1;
    for(i;i<input[0];i++){
        total = total + input[i];
    }
    avg = total / (input[0] - 1);
}

void *Compute_Max(void *ptr){
    int *input = (int *) ptr;
    max = input[1];
    int i = 1;
    for(i;i<input[0];i++){
        if(max < input[i]){
            max = input[i];
        }
    }
}

void *Compute_Min(void *ptr){
    int *input = (int *) ptr;
    int i = 1;
    min = input[1];
    for(i;i<input[0];i++){
        if(min > input[i]){
            min = input[i];
        }
    }
}


void main(int argc, char *argv[]){
    int copy[argc];
    copy[0] = argc; //將argc放入陣列[0]
    int i = 1;
    for(i; i<(argc); i++){
        copy[i] = atoi(argv[i]);
    }
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, Compute_Avg, (void*) copy);
    pthread_create(&thread2, NULL, Compute_Min, (void*) copy);
    pthread_create(&thread2, NULL, Compute_Max, (void*) copy);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    printf("The average:  %f\n", avg);
    printf("The minimum:  %d\n", min);
    printf("The maximum:  %d\n", max);
}
