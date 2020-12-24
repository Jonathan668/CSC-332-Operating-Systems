/* Jonathan So Task 1 
Question 3. Repeat part 2 (by writing a new C program) as per the following procedure: (a) Read the next 75 characters from source.txt, 
and among characters read, replace each character ’5’ with character ‘O’’ and all characters are then written in destination.txt
(b) Write characters "ABC" into file destination.txt (c) Repeat the previous steps until the end of file source.txt. The last read step may not have 75
characters.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //Need for close


int main (int argc, char* argv[])
{
    char* filepath1 = argv[1];
    char* filepath2 = argv[2];
    int returnval1;
    int returnval2;
    int fd1;
    int fd2;
    char buffer[100]; //size of our buffer
    int write_bytes_counter = 0; //Use this to keep track of the number of bytes written 
    if(3 != argc)
{

    printf("\n Usage : \n");
    return 1;
}
     errno = 0;

    // Check first file existence
    returnval1 = access (filepath1, F_OK);
    if (returnval1 == 0)
        printf ("\n %s exists\n", filepath1);
    else
    {
        if (errno == ENOENT)
            printf ("%s does not exist\n", filepath1);
        else if (errno == EACCES)
            printf ("%s is not accessible\n", filepath1);
            return 0;
    }

    // Check second file existence
    returnval2 = access (filepath2, F_OK);
    if (returnval2 == 0)
        printf ("\n %s exists\n", filepath2);
    else
    {
        if (errno == ENOENT)
            printf ("%s does not exist\n", filepath2);
        else if (errno == EACCES)
            printf ("%s is not accessible\n", filepath2);
            return 0;
    }

    // Check read access for first file...
    returnval1 = access (filepath1, R_OK);
    if (returnval1 == 0)
        printf ("\n %s has reading access\n", filepath1);
    //If there's no read access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have reading access\n", filepath1);
    }

    // Check read access for second file...
    returnval2 = access (filepath2, R_OK);
    if (returnval2 == 0)
        printf ("\n %s has reading access\n", filepath2);
    //If there's no read access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have reading access\n", filepath2);
    }

    // Check write access for first file...
    returnval1 = access (filepath1, W_OK);
    if (returnval1 == 0)
        printf ("\n %s has writing access\n", filepath1);
    //If there's no write access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have writing access\n", filepath1);
    }

    // Check write access for first file...
    returnval2 = access (filepath2, W_OK);
    if (returnval2 == 0)
        printf ("\n %s has writing access\n", filepath2);
    //If there's no write access, it just prints that it don't exist.
    else{
        printf ("\n  %s doesn't have writing access\n", filepath2);
    }

    //Open first file
    fd1 = open(argv[1], O_RDONLY); //We open the first file in reading mode
    if(-1 == fd1)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n %s opened successfully for reading\n", filepath1);
    }

    //Open second file
    fd2 = open(argv[2], O_WRONLY); //We open the seond file in writing mode
    if(-1 == fd2)
    {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else
    {
    printf("\n %s opened successfully for writing\n", filepath2);
    }

    //Copying content from first file to second file
    while((write_bytes_counter = read(fd1, buffer, 75))) //While we are reading from the file
    {
            for(int i = 0; i < 75; i++){  // For every 75 characters
		if(buffer[i] == '5')  // If there is a '5'
		   buffer[i] = 'O';  //It gets replaced with a 'O'
	    }
	    write_bytes_counter = write(fd2, buffer, write_bytes_counter); 
            write_bytes_counter = write(fd2, "ABC", 3); //Write the bytes we read from each iteration along with "ABC" at the end
    }
    printf("\n Copied successfully!\n");

    //Closing first file after processing.
    if(close(fd1) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n %s closed successfully\n", filepath1); //CLose is succesful if return code is 0.
    }
 
    //Closing second file after processing.
    if(close(fd2) < 0){ //A return code 0 means the close succeeded, so if it's not 0, 
                    //then it failed.
    printf("\n close() failed with error [%s]\n",strerror(errno));
    return 1;
    }
    else{
    printf("\n %s closed successfully\n", filepath2); //CLose is succesful if return code is 0.
    }
    return 0;
}
