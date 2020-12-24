#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int northFarmer = 1; //initialize our north bound farmers
int southFarmer = 1; //initialize our south bound farmers
pthread_mutex_t lock; //lock

void* northBoundThread(void* thread1){  //North Bound Thread
    pthread_mutex_lock(&lock); //grant thread access to lock
    printf("North Tunbridge #%d farmer can cross the bridge\n", northFarmer);
    printf("North Tunbridge #%d is traveling on the bridge…\n", northFarmer);
    sleep(3);
    printf("North Tunbridge #%d farmer has left the bridge\n\n", northFarmer);
    northFarmer++; //release the lock
    pthread_mutex_unlock(&lock);
}

void* southBoundThread(void* thread2){  //South Bound Thread
    pthread_mutex_lock(&lock); //grant thread access to lock
    printf("South Tunbridge #%d farmer can cross the bridge\n", southFarmer);
    printf("South Tunbridge #%d is traveling on the bridge…\n", southFarmer);
    sleep(3);
    printf("South Tunbridge #%d farmer has left the bridge\n\n", southFarmer);
    southFarmer++;
    pthread_mutex_unlock(&lock); //release the lock
}

int main(){
    for(int i = 0; i <=1 ; i++){
        pthread_t thread1, thread2; //thread ids
        pthread_create(&thread1, NULL, northBoundThread, NULL); //create thread 1
        pthread_create(&thread2, NULL, southBoundThread, NULL); //create thread 2
        pthread_join(thread1, NULL); //join thread 1
        pthread_join(thread2, NULL); //join thread 2
    }
    return 0;
}
