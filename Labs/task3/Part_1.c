/* Jonathan So Task 3
Part 1 Write a program where a child is created to execute command that tells you the date and time in
Unix. Use execl(...). Note: you need to specify the full path of the file name that gives you date and
time information. Announce the successful forking of child process by displaying its PID. */

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
        printf("Child forked successfully, child pid is: %d\n", getpid()); //Child message
	execl("/bin/date", "date", NULL);  //execute the location of unix date file
    }
    else{
        waitpid(pid, &status, 0);
        printf("Child Process Complete\n");
        printf("Parent Process Complete\n");
    }

}
