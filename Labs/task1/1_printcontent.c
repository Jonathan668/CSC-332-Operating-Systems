/* Jonathan So Task 1 
Question 1. Write a C program to implement a command called printcontent that takes a (text) file name as
argument and display its contents. Report an appropriate message if the file does not exist or can’t
be opened (i.e. the file doesn’t have read permission). You are to use open(), read(), write() and
close() system calls.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //Need for close


int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
    int fd;
    char buffer[10]; //size of our buffer
    int write_bytes_counter = 0; //Use this to keep track of the number of bytes written 
    if(2 != argc)
{

    printf("\n Usage : \n");
    return 1;
}
     errno = 0;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf ("\n %s exists\n", filepath);
    else
    {
        if (errno == ENOENT)
            printf ("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible\n", filepath);
            return 0;
    }

    // Check read access ...
    //For read access, second argument is replaced with R_OK.
    returnval = access (filepath, R_OK);
    if (returnval == 0)
        printf ("\n %s has reading access\n", filepath);
    //If there's no read access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have reading access\n", filepath);
    }

    // Check write access ...
    //For read access, second argument is replaced with W_OK.
    returnval = access (filepath, W_OK);
    if (returnval == 0)
        printf ("\n %s has writing access\n", filepath);
    //If there's no write access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have writing access\n", filepath);
    }

    //Open file
    fd = open(argv[1], O_RDONLY);
    if(-1 == fd)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n Open() Successful\n");
    }
    
    //Displaying content of the file
    while((write_bytes_counter = read(fd, buffer, 10))) //We read 10 bytes from the file
        {
                write_bytes_counter = write(1,buffer,write_bytes_counter); //write the bytes we read
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
