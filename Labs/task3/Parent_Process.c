/* Jonathan So Task 3
Write a C program and call it Parent_Process.c. Execute the files as per the following procedure using
execv system call. Use sleep system calls to introduce delays.
[Step 3] Fork a child process, say Child 1 and execute Process_P1. This will create two destination files
according to Step 1.
[Step 4] After Child 1 finishes its execution, fork another child process, say Child 2 and execute
Process_P2 that accomplishes the procedure described in Step 2.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()

int main(){

    pid_t pid1; //Child 1
    pid_t pid2; //Child 2

    int status1 = 0;
    //Fork Child 1
    pid1 = fork();

    if (pid1 < 0) { //Error forking
        fprintf(stderr, "Fork Failed");
         return 1;
    }

    else if (pid1 == 0){ //Child 1 Process
       printf("I am child one, my pid is: %d\n", getpid());
       char *const argv[] = {"Process_P1", NULL}; //store Process_P1 filename in char *
       execv(argv[0], argv); //pass it into execute
       printf("EXECV failed\n"); //will only print if the execution fails
    }

    else{ //Parent Process

        sleep(1); // sleep system call for delay
        int status2 = 0;
        //Fork Child 2
    	pid2 = fork();

    	if (pid2 < 0) { //Error forking
        	fprintf(stderr, "Fork Failed");
         	return 1;
    	}

    	else if (pid2 == 0){ //Child 2 Process
       	printf("\nI am child two, my pid is: %d\n", getpid());
        char *const argv[] = {"Process_P2", NULL}; //store Process_P2 filename in char *
        execv(argv[0], argv); //pass it into execute
        printf("EXECV failed\n"); //will only print if the execution fails

    	}
        else{
           waitpid(pid1, &status1, 0); //Parent have to wait for child 1
           waitpid(pid2, &status2, 0); //Parent have to wait for child 2
           printf("\nChildren Process Complete\n");
           printf("Parent Process Complete\n");
        }
    }
    return 0;
}


