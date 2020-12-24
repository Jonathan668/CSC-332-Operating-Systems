#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4  //I have 4 cores and 4 threads on my computer

void* threadFunction(void* tid); //function called by all threads

int global_num = 1;  //global variable shared by all the threads

void* threadFunction(void* tid){
    int max_Num_of_Divisor = 1; //initialize our max number of divisor to 1
    int num = 1; // initialize the integer with the  largest number of divisor to 1, smallest possible number within range that has a divisor
    int n;
    for(n = 2; n <= 10000; n++){ //iterate through the range of integers
        int divisor;
        int divisor_Count = 0;

        for(divisor = 1; divisor <= n; divisor++){ //for each integer, check the divisors
            if(n % divisor == 0){  //if the integer is divisible  by the divisor,
                divisor_Count++;    //increment the divisor_Count
            }
        }

        if(divisor_Count > max_Num_of_Divisor){ //if the divisor_Count is greater than the current largest number of divisors
            max_Num_of_Divisor = divisor_Count;  // the value of divisor_Count becomes the new largest number of divisors
            //global_mNOD = divisor_Count;
            num = n; //the integer n with the largest number of divisors becomes the new value of num
            global_num = n; // update the global variable
        }
    }
    printf("The integer with the largest number of divisors in the range 1 to 10000 using %d threads is: %d\n", NUM_THREADS, global_num); //We print the  value of our global num, which will hold the largest number of divisors
    pthread_exit(NULL);  
}

int main(int argc, char *argv[]){
    int i = 0;
    pthread_t tid;
    clock_t start = clock(); //start timing the process
    pthread_create(&tid, NULL, threadFunction, (void*)&i); //create the threads
    pthread_join(tid, (void**)&i);  //join the threads
    clock_t stop = clock(); //stop clock after threads have joined and process has completed
    printf("Time elapsed in ms: : %f\n", (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC); //Calculates the time elapsed from the start to end of the calculation in milliseconds
}
