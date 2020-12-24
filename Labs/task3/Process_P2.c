/* Jonathan So Task 3
Copy the contents of source.txt into destination1.txt and destination2.txt as
per the following procedure:
1. Read the next 50 characters from source.txt, and among those characters write chars 5 and 8 only
to destination1.txt
2. Then the next 100 characters are read from source.txt and written in destination2.txt. */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //Need for close


int main (int argc, char* argv[])
{
    int fd1;
    int fd2;
    int fd3;
    int reader;
    char buffer[150]; //size of our buffer

     errno = 0;

    //Open source.txt
    fd1 = open("source.txt", O_RDONLY); //We open source.txt in reading mode
    if(-1 == fd1)
    {
    printf("\n source.txt open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n source.txt opened successfully for reading\n");
    }

    //Open destination1.txt file
    fd2 = open("destination1.txt", O_WRONLY); //We open destination1.txt in writing mode
    if(-1 == fd2)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n destination1.txt opened successfully for writing\n");
    }

    //Open destination2.txt file
    fd3 = open("destination2.txt", O_WRONLY); //We open destination2.txt in writing mode
    if(-1 == fd3)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n destination2.txt opened successfully for writing\n");
    }
    //Copying content from first file to second and third file
    int i = 0; //increment as we read
    while((reader = read(fd1, buffer, 1)) > 0) //While there's content being read
    {
           if (i < 50){
                if (buffer[0] == '5') {          //if the character is 5
                    write(fd2, buffer, reader);  // we write to destination1
                    i++;
                }
                else if (buffer[0] == '8'){      //if the character is 8
                    write(fd2, buffer, reader);  // we write to destination1
                    i++;
                }
                i++;       //incrememt 
           }
           else if(i < 150){                  // we read the next 100 characters
                if (buffer[0] == '\n') {      //we account for new line characters
                    write(fd3, buffer, 1);
                }else{
                    write(fd3, buffer, reader); //we write to destination2
                    i++;
                }

            }
    }
    printf("\n Copied successfully!\n");

    //Closing first file after processing.
    if(close(fd1) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n source.txt close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n source.txt closed successfully\n"); //CLose is succesful if return code is 0.
    }
 
    //Closing second file after processing.
    if(close(fd2) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n destination1.txt close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n destination1.txt closed successfully\n"); //CLose is succesful if return code is 0.
    }

    //Closing third file after processing.
    if(close(fd3) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n destination2.txt close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n destination2.txt closed successfully\n"); //CLose is succesful if return code is 0.
    }

    return 0;
}
