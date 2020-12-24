#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 10000
#define REQUESTS 1000

int start, arr[REQUESTS], position, min, x;

//counters for each algorithm
int fcfsCount = 0;
int sstfCount = 0;
int scanCount = 0;
int cscanCount = 0;
int lookCount = 0;

int i, j;

int diff(int a, int b) { //function used to calculate the difference
    int c;
    c = a - b;

    if(c < 0)
        return -c;
    else
        return c;
}


void FCFC(int arr[]){  
    for(i = 0; i < REQUESTS; i++) {
         x = diff(x, arr[i]); 
         if(x < 0) { //account for negatives
            x = -x;
         }
         fcfsCount += x; //increment the FCFS counter by x 
         x = arr[i];
    }
}

void SSTF(int arr[]){
    for(i = 0; i < REQUESTS; i++) {
         min = diff(arr[i], x); //unaccessed track computed as the minimum distance between the current position of the array and start 
         position = i;
         for(j = i; j < REQUESTS; j++) {
             if(min > diff(x, arr[j])) { //swap elements of the array based on their distance from each other
                 position = j;
                 min = diff(x, arr[j]);
             }
         }
         sstfCount += diff(x, arr[position]); //increment the sstf counter by the difference between x and position of our array
         x = arr[position]; //accessed track is the new start 
         arr[position] = arr[i];
         arr[i] = x;
    }
}

void SCAN(int arr[]){
    position = 0;
    for(i = 0; i < REQUESTS; i++) {  //sort the array 
        for(j = i; j < REQUESTS - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                x = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = x;
            }
        }
    }

   for(i = 0; i < REQUESTS; i++) { //check to see if the element in array is less than start
        if(arr[i] < start) {
            position++;   //increment the position 
        }
    }
    
    for(i = 0; i < position; i++) {  // sort the elements that are within 0 - position 
       for(j = 0; j < position - i - 1; j++) {
           if(arr[j] < arr[j + 1]) {
               x = arr[j];
               arr[j] = arr[j + 1];
               arr[j + 1] = x;
           }
       }
    }

    x = start;

    for(i = 0; i < position; i++) { //starting from 0 to position
        scanCount += diff(arr[i], x); //increment the scanCount counter by the difference between value of our array at index i and x
        x = arr[i];
    }

    //used to get the diff from zero or to get the same value
    scanCount += diff(x, 0);
    x = 0;

    for(i = position; i < REQUESTS; i++) { //from position to the highest value 
        scanCount += diff(arr[i], x); //increment the scanCount counter by the difference between value of our array at index i and x
        x = arr[i];
    }
}

void CSAN(int arr[]){
    position = 0;

    for(i = 0; i < REQUESTS; i++) { //sort the array
        for(j = 0; j < REQUESTS - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                x = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = x;
            }
        }
    }

    for(i = 0; i < REQUESTS; i++) { //check to see if the element in array is less than start
        if(arr[i] < start) {
            position++; //increment the position
        }
    }

    x = start;
    for(i = position; i < REQUESTS; i++) { //from position to the highest value 
        cscanCount += diff(x, arr[i]); //increment the cscanCount counter by the difference between x and the value of our array at index i
        x = arr[i];
    }
    
    //used to save the boundary value
    cscanCount += diff(CYLINDERS - 1, x);
    x = 0;


    for(i = 0; i < position; i++) { //starting from 0 to position
        cscanCount += diff(x, arr[i]); //increment the cscanCount counter by the difference between x and the value of our array at index i
        x = arr[i];
    }
}

void LOOK(int arr[]){
    position = 0;

    for(i = 0; i < REQUESTS; i++) { //sort the array
        for (j = 0; j < REQUESTS - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                x = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = x;
            }
        }
    }

    for (i = 0; i < REQUESTS; i++) { //check to see if the element in array is less than start
        if (arr[i] < start) {
            position++; //increment the position
        }
    }

    for (i = 0; i < position; i++) { // sort the elements that are within 0 - position 
        for (j = 0; j < position - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                x = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = x;
            }
        }
    }

    x = start;
    for(i = 0; i < position; i++) { //starting from 0 to position
        lookCount += diff(arr[i], x); //increment the lookCount counter by the difference between value of our array at index i and x
        x = arr[i];
    }

    for(i = position; i < REQUESTS; i++) { //from position to the highest value
        lookCount += diff(arr[i], x); //increment the lookCount counter by the difference between value of our array at index i and x
        x = arr[i];
    }
}

int main(int argc, char *argv[]) {
    
    start = atoi(argv[1]);
    
    if(argc != 2) {

	printf("Usage: Compile program with starting index from 0-9999. Ex. ./diskScheduling 356\n");
	exit(-1);
    }

    for(i = 0; i < REQUESTS; i++) { //insert 1000 random requests
	arr[i] = rand() % CYLINDERS;
    }

    x = start;

    //call each algorithm
    FCFC(arr);
    SSTF(arr);
    SCAN(arr);
    CSAN(arr);
    LOOK(arr);

    printf("Algorithm \t Total head movements\n");
    printf("FCFS \t\t %d\n", fcfsCount);
    printf("SSTF \t\t %d\n", sstfCount);
    printf("SCAN \t\t %d\n", scanCount);
    printf("CSCAN \t\t %d\n", cscanCount);
    printf("LOOK \t\t %d\n", lookCount);
    return 0;
}
