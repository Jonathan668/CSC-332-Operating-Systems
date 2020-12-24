/* Jonathan So Task 2
Part 2 Consider the parent process as P. The program consists of fork() system call statements placed at
different points in the code to create new processes Q and R. The program also shows three variables: a,
b, and pid - with the print out of these variables occurring from various processes. Show the values of pid,
a, and b printed by the processes P, Q, and R.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    //parent P
    int a=10, b=25, fq=0, fr=0;
    fq=fork(); // fork a child - call it Process Q
    if(fq==0){ // Child successfully forked
       a=a+b; 
       printf("Process Q: \n Value of a: %d\n Value of b: %d\n Value of process id: %d\n", a, b, getpid()); // print values of a, b, and process_id

       fr=fork(); // fork another child - call it Process R
       if(fr!=0){
          b=b+20;
          printf("Process Q: \n Value of a: %d\n Value of b: %d\n Value of process id: %d\n", a, b, getpid()); //print values of a, b, and process_id
        }else{
          a=(a*b)+30;
          printf("Process R: \n Value of a: %d\n Value of b: %d\n Value of process id: %d\n", a, b, getpid()); //print values of a, b, and process_id
       }
    }else{ //Parent process
       b=a+b-5;
       printf("Process P: \n Value of a: %d\n Value of b: %d\n Value of process id: %d\n", a, b, getpid()); //print values of a, b, and process_id
     }
}
