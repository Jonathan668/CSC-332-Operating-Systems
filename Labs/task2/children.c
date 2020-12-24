/* Jonathan So Task 2 
Part 1 Write a program children.c, and let the parent process produce two child processes. One prints
out "I am child one, my pid is: " PID, and the other prints out "I am child two, my pid is: " PID. Guarantee
that the parent terminates after the children terminate (Note, you need to wait for two child processes
here). Use the getpid() function to retrieve the PID.
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
    }

    else{ //Parent Process
        int status2 = 0;
        //Fork Child 2
    	pid2 = fork();

    	if (pid2 < 0) { //Error forking
        	fprintf(stderr, "Fork Failed");
         	return 1;
    	}

    	else if (pid2 == 0){ //Child 2 Process
       	printf("I am child two, my pid is: %d\n", getpid());
    	}
        else{
           waitpid(pid1, &status1, 0); //Parent have to wait for child 1
           waitpid(pid2, &status2, 0); //Parent have to wait for child 2
           printf("Children Process Complete\n");
           printf("Parent Process Complete\n");
        }
    }
    return 0;
}
