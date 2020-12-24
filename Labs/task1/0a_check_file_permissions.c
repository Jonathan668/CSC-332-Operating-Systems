/* Jonathan So Task 1 
Question 0. (a) Extend code snippet 1 to check 
for read and write access permissions of a given file*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
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

    return 0;
}
