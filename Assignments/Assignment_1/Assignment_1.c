//Jonathan So CSC 332 Assignment 1

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()

int main(){

    int fd[2];
    pid_t pid1; //Child 1
    pid_t pid2; //Child 2

    //Creating the pipe
    if (pipe(fd) == -1) {
    fprintf(stderr,"Pipe failed");
    return 1;
    }

    //Fork Child 1
    pid1 = fork();

    if (pid1 < 0) { //Error forking
        fprintf(stderr, "Fork Failed");
         return 1;
    }

    else if (pid1 == 0){ //Child 1 Process
       close(fd[0]); //Close unused end of the pipe
       dup2(fd[1], 1); //Duplicate the output
       execlp("ls", "ls", "-F", NULL); //Execute  ls -F command
    }

    else{ //Parent Process

       //Fork Child 2
       pid2 = fork();

       if (pid2 < 0) { //Error forking
           fprintf(stderr, "Fork Failed");
           return 1;
       }

       else if (pid2 == 0){ //Child 2 Process
          close(fd[1]); //Close unused end of the pipe
          dup2(fd[0], 0); //Duplicate the input
          execlp("nl", "nl", NULL); //Execute nl command
       }
       close(fd[1]); //Close write end of the pipe
       close(fd[0]); //Close read end of the pipe
       wait(NULL); //Parent have to wait for child 1
       wait(NULL); //Parent have to wait for child 2
    }
    return 0;
}
