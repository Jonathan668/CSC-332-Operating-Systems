/* Jonathan So Task 4
Part 1 Write a special simple command interpreter that takes command and its arguments. This interpreter
is a program where the main process creates a child process to execute the command using exec()
family functions. After executing the command, it asks for a new command input (i.e., parent wait for
child). The interpreter program will get terminated when the user enters quit. */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
    char line[BUFFER_SIZE]; //character array that holds our input commands
    printf("Type 'quit' to exit\n"); 
    while(fgets(line, BUFFER_SIZE, stdin)) { //while we are getting inout from user
        char *c = strchr(line, '\n'); //accounts for new line after user writes command
        if(c){
            *c = 0;
        }
        if(strcmp(line, "quit") == 0) //if the input is equal to "quit" program terminates
            break;

        char *token = strtok(line, " ");  //input broken into tokens
        int i = 0;
        while(token != NULL){
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        pid_t pid; //Child

    	int status = 0;

    	//Fork Child
    	pid = fork();

    	if (pid < 0) { //Error forking
        	fprintf(stderr, "Fork Failed");
         	return 1;
    	}
    	else if (pid == 0){ //Child Process
		execvp(argv[0], argv);  //execute the command from input
                printf("EXECVP FAILED\n"); //will print if the execution fails
                exit(1);
    	}
    	else{//Parent Process
        	waitpid(pid, &status, 0);
        	printf("\nEnter new command: ");
    	}
   }
   return 0;
}
