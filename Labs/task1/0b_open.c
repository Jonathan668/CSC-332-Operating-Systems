/* Jonathan So Task 1 
Question 0. (b) ) Write a C program where open system call creates a new file 
(say, destination.txt) and then opens it*/

//I builded upon the sample open code from the lab pdf.
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //Need for close

int main(int argc, char *argv[])
{
    int fd;
    if(2 != argc)
{

    printf("\n Usage : \n");
    return 1;
}

    errno = 0;
    //We add a bitwise OR O_CREAT, so the file is created if it doesn't exists.
    fd = open(argv[1], O_RDONLY|O_CREAT);
    if(-1 == fd)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n Open() Successful\n");
    }
    //Closing the file after processing.
    if(close(fd) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n Close() Successful\n"); //CLose is succesful if return code is 0.
    }
    return 0;
}

