/* Jonathan So Task 3
Part 2 Write a program where a child is created to execute a command that shows all files (including hidden files)
in a directory with information such as permissions, owner, size, and when last modified. Use execvp(...).
Announce the successful forking of child process by displaying its PID. */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()

int main(){

    pid_t pid; //Child

    int status = 0;

    //Fork Child
    pid = fork();

    if (pid < 0) { //Error forking
        fprintf(stderr, "Fork Failed");
         return 1;
    }
    else if (pid == 0){ //Child Process
        printf("Child forked successfully, child pid is: %d\n", getpid());
	char *argv[] = {"ls", "-l", NULL}; //store commands into argv
        execvp(argv[0],argv); //execute the commands in argv
    }
    else{
        waitpid(pid, &status, 0);
        printf("Child Process Complete\n");
        printf("Parent Process Complete\n");
    }

}

