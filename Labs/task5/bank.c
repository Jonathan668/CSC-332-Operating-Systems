#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()
#include "sem.h"

#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

////////////////////////////////////////////////////////////////////////////////////////////////////

//Create 3 files to to keep track of the number of times dad, son1, son2 show interest in CS
FILE *fp5, *fp6, *fp7;

////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables

        ////////////////////////////////////////////////////////////////////////////////////////////////////
	// semaphore
        int sem;

        //counters to keep track of the number of times interest is shown
        int dadCount, son1Count, son2Count;

        //create semaphore
        sem = semget(IPC_PRIVATE,1, 0666|IPC_CREAT);
	sem_create(sem,1);
        ////////////////////////////////////////////////////////////////////////////////////////////////////

	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //Initialize our counters
        fp5 = fopen("dad_time", "w");
        dadCount = 0;
        fprintf(fp5, "%d\n", dadCount);
	fclose(fp5);

        fp6 = fopen("son1_time", "w");
        son1Count = 0;
        fprintf(fp6, "%d\n", son1Count);
        fclose(fp6);

        fp7 = fopen("son2_time", "w");
        son2Count = 0;
        fprintf(fp7, "%d\n", son2Count);
        fclose(fp7);
        ////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{
                        ////////////////////////////////////////////////////////////////////////////////////////////////////
                        P(sem);	 //Lock critical section

                        //During the dad process, we keep track of the number of times the sons express interest in CS

                        fp6 = fopen("son1_time", "r+"); // We use r+ for read and write access
			fscanf(fp6, "%d", &son1Count);
			fseek(fp6, 0L, 0);
			son1Count++;	     // Increment the number of times son 1 expresses interest in CS
                        printf("Number of times son 1 expressed interest in critical section = %d \n", son1Count);
			fprintf(fp6, "%d\n", son1Count);
			fclose(fp6);

			fp7 = fopen("son2_time", "r+"); // We use r+ for read and write access
                        fscanf(fp7, "%d", &son2Count);
                        fseek(fp7, 0L, 0);
                        son2Count++;         // Increment the number of times son 2 expresses interest in CS
                        printf("Number of times son 2 expressed interest in critical section = %d \n", son2Count);
                        fprintf(fp7, "%d\n", son2Count);
                        fclose(fp7);
                        ////////////////////////////////////////////////////////////////////////////////////////////////////

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */
                        ////////////////////////////////////////////////////////////////////////////////////////////////////
                        V(sem);  //Exit critical section
                        ////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
                                ////////////////////////////////////////////////////////////////////////////////////////////////////
                                P(sem);  //Lock critical section

                                //During son 1 process, we keep track of the number of times dad and son 2 express interest in CS

                                fp5 = fopen("dad_time", "r+"); // We use r+ for read and write access
                                fscanf(fp5, "%d", &dadCount);
                                fseek(fp5, 0L, 0);
                                dadCount++;         // Increment the number of times dad expresses interest in CS
                                printf("Number of times dad expressed interest in critical section = %d \n", dadCount);
                                fprintf(fp5, "%d\n", dadCount);
                                fclose(fp5);

                                fp7 = fopen("son2_time", "r+"); // We use r+ for read and write access
                                fscanf(fp7, "%d", &son2Count);
                                fseek(fp7, 0L, 0);
                                son2Count++;         // Increment the number of times son 2 expresses interest in CS
                                printf("Number of times son 2 expressed interest in critical section = %d \n", son2Count);
                                fprintf(fp7, "%d\n", son2Count);
                                fclose(fp7);
                                ////////////////////////////////////////////////////////////////////////////////////////////////////

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
                                ////////////////////////////////////////////////////////////////////////////////////////////////////
                                V(sem);  //Exit critical section
                                ////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
                                        ////////////////////////////////////////////////////////////////////////////////////////////////////
                                        P(sem);  //Lock critical section

                                        //During son 2 process, we keep track of the number of times dad and son 1 express interest in CS

                                        fp5 = fopen("dad_time", "r+"); // We use r+ for read and write access
                                        fscanf(fp5, "%d", &dadCount);
                                        fseek(fp5, 0L, 0);
                                        dadCount++;         // Increment the number of times dad expresses interest in CS
                                        printf("Number of times dad expressed interest in critical section = %d \n", dadCount);
                                        fprintf(fp5, "%d\n", dadCount);
                                        fclose(fp5);

                                        fp6 = fopen("son1_time", "r+"); // We use r+ for read and write access
                                        fscanf(fp6, "%d", &son1Count);
                                        fseek(fp6, 0L, 0);
                                        son1Count++;       // Increment the number of times son 1 expresses interest in CS
                                        printf("Number of times son 1 expressed interest in critical section = %d \n", son1Count);
                                        fprintf(fp6, "%d\n", son1Count);
                                        fclose(fp6);
                                        ////////////////////////////////////////////////////////////////////////////////////////////////////


					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
                                        ////////////////////////////////////////////////////////////////////////////////////////////////////
                                        V(sem);  //Exit critical section
                                        ////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}
