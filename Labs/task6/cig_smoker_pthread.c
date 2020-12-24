#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> // time()
#include <pthread.h>

pthread_mutex_t lock; //lock
pthread_mutex_t agentLock; //lock for agent
pthread_mutex_t smokerPaperLock; //lock for smoker with paper
pthread_mutex_t smokerTobaccoLock; //lock for smoker with tobacco
pthread_mutex_t smokerMatchesLock; //lock for smoker with matches

//Thread functions used by threads
void* agentThread();
void* smokerPaperThread();
void* smokerTobaccoThread();
void* smokerMatchesThread();

int num = 10; //number of times agent places ingredients

void* agentThread(){ //agent function
    while(num > 0){
	    pthread_mutex_lock(&lock); //grant thread access to lock
	    int num = rand() % 3; //random number of ingredients agent place
        if (num == 0){ //first case
            printf("Agent puts matches and paper on the table\n");
            sleep(1);
            pthread_mutex_unlock(&smokerTobaccoLock); //signal the smoker with tobacco
        }
        else if (num == 1){ //second case
            printf("Agent puts tobacco and paper on the table\n");
            sleep(1);
            pthread_mutex_unlock(&smokerMatchesLock); //signal the smoker with matches
        }
        else{ //third case
            printf("Agent puts tobacco and matches on the table\n");
            sleep(1);
            pthread_mutex_unlock(&smokerPaperLock); //signal the smoker with paper
        }
	pthread_mutex_unlock(&lock); //done with lock
	pthread_mutex_lock(&agentLock); //put agent to sleep
    }
}

void* smokerPaperThread(){ //smokerPaper function
    while(num > 0){
    	pthread_mutex_lock(&smokerPaperLock); //put smokerPaper to sleep
    	pthread_mutex_lock(&lock); //grant thread access to lock
    	printf("Smoker with paper picks up tobacco and matches from the table, rolls and smokes a cigarette\n\n");
    	pthread_mutex_unlock(&agentLock); //signal the agent
    	pthread_mutex_unlock(&lock); //done with lock
    	num--;
    }
}

void* smokerTobaccoThread(){ //smokerTobacco function
    while(num > 0){
    	pthread_mutex_lock(&smokerTobaccoLock); //put smokerTobacco to sleep
    	pthread_mutex_lock(&lock); //grant thread access to lock
    	printf("Smoker with tobacco picks up matches and paper from the table, rolls and smokes a cigarette\n\n");
    	pthread_mutex_unlock(&agentLock); //signal the agent
    	pthread_mutex_unlock(&lock); //done with lock
    	num--;
    }
}

void* smokerMatchesThread(){ //smokerMatches function
    while(num > 0){
    	pthread_mutex_lock(&smokerMatchesLock); //put smokerMatches to sleep
    	pthread_mutex_lock(&lock); //grant thread access to lock
    	printf("Smoker with matches picks up tobacco and paper from the table, rolls and smokes a cigarette\n\n");
    	pthread_mutex_unlock(&agentLock);  //signal the agent
    	pthread_mutex_unlock(&lock); //done with lock
    	num--;
    }
}

int main(){
    srand(time(0)); //used for rand number
    
    //initial states of our locks
    pthread_mutex_lock(&agentLock);
    pthread_mutex_lock(&smokerPaperLock);
    pthread_mutex_lock(&smokerTobaccoLock);
    pthread_mutex_lock(&smokerMatchesLock);
    pthread_mutex_unlock(&lock);
    
    pthread_t agent, smokerPaper, smokerTobacco, smokerMatches; //thread ids

    for(int i = 0; i <=1 ; i++){
        pthread_create(&agent, NULL, agentThread, NULL); //create agent thread 
        pthread_create(&smokerPaper, NULL, smokerPaperThread, NULL); //create smokerPaper thread 
	pthread_create(&smokerTobacco, NULL, smokerTobaccoThread, NULL); //create smokerTobacco thread 
	pthread_create(&smokerMatches, NULL, smokerMatchesThread, NULL); //create smokerMatches thread 
        pthread_join(agent, NULL); //join agent thread because other threads work with this thread
    }
    
    printf("Process completed! Agent is out of ingredients\n");
    return 0;
}
