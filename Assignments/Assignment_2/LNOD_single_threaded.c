#include <stdio.h>
#include <time.h>

int main(){
    int max_Num_of_Divisor = 1; //initialize our max number of divisor to 1
    int num = 1; // initialize the integer with the  largest number of divisor to 1, smallest possible number within range that has a divisor
    int n;
    clock_t start = clock(); //start timing the process

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
            num = n; //the integer n with the largest number of divisors becomes the new value of num
        }
    }
    clock_t stop = clock(); // stop clock after calculation has completed
    printf("The integer with the largest number of divisors in the range 1 to 10000 using 1 thread is: %d\n", num); //We print the  value of num, which will hold the largest number of divisors
    printf("Time elapsed in ms: : %f\n", (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC); //Calculates the time elapsed from the start to end of the calculation in milliseconds
}
