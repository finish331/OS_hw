#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* return 0 if successful or -1 if unsuccessful */
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);

/* resource checking*/
int request[NUMBER_OF_RESOURCES];
int release[NUMBER_OF_RESOURCES];

pthread_mutex_t mutex;
void *create(void *params);
int safe(int process);
int i = 0;



int request_resources(int customer_num, int request[]) {

    int j = 0;
    printf("P%d requested the following: {%d, %d, %d}\n", customer_num, request[0], request[1], request[2]);

    for(i=0; i<NUMBER_OF_RESOURCES; i++) {

        if(request[i] <= need[i]) {

            if(request[i] <= available[i]) {

                available[i] = available[i] - request[i]; //available allocation

                int condition = safety(customer_num);

                allocation[customer_num][i] = allocation[customer_num][i] + request[i];

                need[customer_num][i] = need[customer_num][i] - request[i];

                if(condition==0) {//0= sucess, safe!

                printf("\n");
                printf("   Allocation");
                 printf("    Max");
                 printf("      Need\n");

                    for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {
                        printf("P%d ", i);
                        for(j=0; j<NUMBER_OF_RESOURCES; j++) {
                         printf(" {");
                         printf("%d ", allocation[i][j]);
                         printf("%d ", maximum[i][j]);
                         printf("%d", need[i][j]);
                         printf("}  ");
                        }

                        printf("\n");
                    }

                    return 0; //success!

                }


                else {//unsafe state entered
                    available[i] = available[i] + request[i];

                    allocation[customer_num][i] = allocation[customer_num][i] - request[i];//allocate ammount requested

                    need[customer_num][i] = need[customer_num][i] + request[i]; // how much required by customer

                    printf("Unsafe State\n");
                    return -1;
                }

            }
            else if(request[i] > available[i]) {
                printf("Process will wait since resource requested is too large\n");
                return -1;
            }
        }


        else if(request[i] > need[i]) {//Request is too large pg332
            printf("Error too large of a request\n");
            return -1;
        }

    }

}


int safety(int process) {//are we in a safe state?

    int work[process];
    int finish[process];
    int j = 0;

    work[process] = available;
    finish[process] = -1;

    for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {
         for(j=0; j<NUMBER_OF_RESOURCES; j++) {//test resources with customers
            if(finish[i]==-1 && need[i][j] <= work[i]) {//success formula, if true, fail
                return -1;//fail! unssafe
            }
            else {
                work[i] = work[i] + allocation[i][j];
                finish[i] = 0;
            }
        }
    }

    return 0;//success!
}


//returns a 0 successful or -1 unsuccessful
int release_resources(int customer_num, int release[]) {
    int j = 0;
    for(i=0; i<NUMBER_OF_RESOURCES; i++) {
        available[i] = available[i] - request[i]; //Available algorithm from pg332

        allocation[customer_num][i] = allocation[customer_num][i] + request[i]; //Remove algorithm from pg332

        need[customer_num][i] = need[customer_num][i] - request[i]; //Need algorithm from pg332
    }

    printf("\n");
    printf("   Allocation");
    printf("    Max");
    printf("      Need\n");

    for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {
        printf("P%d ", i);
        for(j=0; j<NUMBER_OF_RESOURCES; j++) {
            printf(" {");
            printf("%d ", allocation[i][j]);
            printf("%d ", maximum[i][j]);
            printf("%d", need[i][j]);
            printf("}  ");
        }

        printf("\n");
    }
    return 0;//Success
}
void *create(void *params) { //creates allocation based on input
    pthread_mutex_lock(&mutex);

    int counter = 0;
    int j =0;
    for(i=0; i<20; i++) {

        counter++;

        for(j=0; j<NUMBER_OF_RESOURCES; j++) {
            request[j] = rand() % (maximum[i][j]+1);
        }


      int  k = rand() % NUMBER_OF_CUSTOMERS;
        i = k;

        request_resources(i, request);

        sleep(1);

        for(j=0; j<NUMBER_OF_RESOURCES; j++) {
            release[j] = rand() % (maximum[i][j]+1);
        }

        release_resources(i, release);
        pthread_mutex_unlock(&mutex);
        pthread_exit(0);
    }
}

int main(int argumentCount, char* argumentArray[]) {

    printf("Available\n{ ");
    int j = 0;

     for(i=1; i<argumentCount; i++) {   //create argument array
        printf("%d ", atoi(argumentArray[i]));
    }
    printf("}");
    printf("\n");
    printf("   Allocation");
    printf("    Max");
    printf("      Need\n");

    for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {
        printf("P%d  ", i);
        for(j=0; j<NUMBER_OF_RESOURCES; j++) {
            allocation[i][j] = 0;
            maximum[i][j] = rand() % (argumentCount+1);
            need[i][j] = maximum[i][j];
            printf(" {");
            printf("%d ", allocation[i][j]);
            printf("%d ", maximum[i][j]);
            printf("%d", need[i][j]);
            printf("}  ");
        }

        printf("\n");
    }


    pthread_t Customer[NUMBER_OF_CUSTOMERS];//Customer threads created

    pthread_attr_t attr;

    pthread_attr_init(&attr);//initialize threads

    pthread_mutex_init(&mutex, NULL);//initialize mutex

     for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {//create multiple threads
        pthread_create(&Customer[i], &attr, create, NULL);
    }

    for(i=0; i<NUMBER_OF_CUSTOMERS; i++) {//join threads
        pthread_join(Customer[i], NULL);
    }

    pthread_mutex_destroy(&mutex); //end threading here
}
