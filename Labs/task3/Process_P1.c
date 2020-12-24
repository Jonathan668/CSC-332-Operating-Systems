/*Jonathan So Task 3
Create two files namely, destination1.txt and destination2.txt with read, write and execute
permissions */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //Need for close

int main()
{
    int fd1 ,fd2;

    errno = 0;
    //We add a bitwise OR O_CREAT, so the file is created if it doesn't exists.
    fd1 = open("destination1.txt", O_RDONLY|O_CREAT);
    if(-1 == fd1)
    {
    printf("\n destination1.txt open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n destination1.txt open() successful\n");
    }
    //Closing the file after processing.
    if(close(fd1) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n destination1.txt close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n destination1.txt close() successful\n"); //CLose is succesful if return code is 0.
    }

   //We add a bitwise OR O_CREAT, so the file is created if it doesn't exists.
    fd2 = open("destination2.txt", O_RDONLY|O_CREAT);
    if(-1 == fd2)
    {
    printf("\n destination2.txt open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n destination2.txt open() successful\n");
    }
    //Closing the file after processing.
    if(close(fd2) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n destination2.txt close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n destination2.txt close() successful\n"); //CLose is succesful if return code is 0.
    }

    return 0;
}
