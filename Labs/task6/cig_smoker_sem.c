#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()
#include "sem.h"
#include <time.h> // time()

int main()
{
    // semaphore
    int sem;

    //smokers with each ingredient
    int smokerPaper, smokerTobacco, smokerMatches;

    //lock and agent
    int lock, agent;

    //create semaphores for lock, agent and each smoker
    lock = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);
    agent = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);
    smokerPaper = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);
    smokerTobacco = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);
    smokerMatches = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);

    //initialize the semaphores
    sem_create(lock,1);
    sem_create(agent,0);
    sem_create(smokerPaper,0);
    sem_create(smokerTobacco,0);
    sem_create(smokerMatches,0);

    int numTimes = 10 ; //number of times agent places ingredients
    int pid, status;
    srand(time(0)); //used for rand number

    pid = fork();
    if (pid == 0){ //agent process
              for(int i = 0; i < numTimes; i++){ //agent randomly hands out 2 out of 3 ingredients 10 times
            	P(lock); //Lock critical section
                int num = rand() % 3; //random number of ingredients agent place
            	if (num == 0){ //first case
            		printf("Agent puts matches and paper on the table\n");
                        sleep(1);
            		V(smokerTobacco); //signal the smoker with tobacco
            	}
                else if (num == 1){ //second case
                        printf("Agent puts tobacco and paper on the table\n");
                        sleep(1);
                        V(smokerMatches); //signal the smoker with matches
                }
                else{ //third case
                        printf("Agent puts tobacco and matches on the table\n");
                        sleep(1);
                        V(smokerPaper); //signal the smoker with paper
                }
                V(lock);
                P(agent);
             }
    }
    else{ //Parent Process
                pid = fork();
		if (pid == 0){// smokerTobacco process
		    while(1){
		        P(smokerTobacco);  //smokerTobacco using CS
                	P(lock);
                	printf("Smoker with tobacco picks up matches and paper from the table, rolls and smokes a cigarette\n\n");
                	V(lock); //Done with CS
                	V(agent); //signal agent to hand out next two random ingredients
		    }
		}else{
                        pid = fork();
		        if (pid == 0){ // smokerPaper proces
		            while(1){
		                P(smokerPaper);  //smokerPaper using CS
				P(lock);
				printf("Smoker with paper picks up tobacco and matches from the table, rolls and smokes a cigarette\n\n");
				V(lock); //Done with CS
				V(agent); //signal agent to hand out next two random ingredients
		            }	
		       }else{
                                pid = fork();
		                if (pid == 0){ //smokerMatches proces
		                    while(1){
		                        P(smokerMatches);  //smokerMatches using CS
                        		P(lock);
                        		printf("Smoker with matches picks up tobacco and paper from the table, rolls and smokes a cigarette\n\n");
                        		V(lock); //Done with CS
                        		V(agent); //signal agent to hand out next two random ingredients
		                    }
		                }else{
		                   pid = wait(&status);
                           	   printf("Process completed! Agent is out of ingredients\n");
		                }
		            }
		  }
	}
	exit(0);
 }
