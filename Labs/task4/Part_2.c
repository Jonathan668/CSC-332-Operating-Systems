/* Jonathan So Task 4
Part 2 There are 10 students enrolled in a course. The course covers x number of chapters from a textbook
(x > 1). In each chapter y number of homework(s) are assigned (y ≥ 1). The average grade for each
homework in all the chapters need to be found out.To solve this, write a program that has the main process 
as Director process, which reads a file containing grades of all homework of all chapters and creates x 
number of Manager processes. Each Manager process will take care of solving a chapter. Each manager process 
will create y number of Worker processes and pass one homework to each of them and they calculate and print
the max and average. The input file should contain the data according to the value of x and y */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Need for wait()
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int students = 10; //10 students
    int manager = 0; //manager process status
    int worker = 0;  //worker process status
    int input; //holds our input
    int chapters = atoi(argv[1]); // converts input number of chapters into int
    int hw = atoi(argv[2]); // converts input number of hws into int
    int totalHw = chapters * hw; //number of children processes that need to be created

    if(argc < 3){
    printf("\n Usage : Enter the number of chapters followed by the number of homeworks \n");
    return 1;
    }

    int *grades[students]; //store grades into array
    for (int i = 0; i < students; i++) 
	{
		grades[i] = (int *) malloc(totalHw * sizeof(int)); //memory allocation

	}

    FILE *fd = fopen("quiz_grades.txt", "r"); //open our textfile in read mode
    for (int i = 0; i < students; i++) {
        for(int j = 0; (j < totalHw) && ( (fscanf(fd, "%d", &input)) ) > 0 ; j++){  //get data from input file
            grades[i][j] = input;
        }
    }
    fclose(fd); //close our textfile after use

    int row = 0;
    int column = 0;
    int total = 0;

    for (int i = 0; i < chapters; i++) {
		manager = fork();
                if (manager < 0) { //manager fork fail
			fprintf(stderr, "Manager Fork Failed");
			return 1;
		}
                else if (manager == 0) {
                    for (int j = 0; j < hw; j++) {
                        worker = fork();
				if (worker < 0) { //worker for fail
				    fprintf(stderr, "Worker Fork Failed");
				    return 1;
				}
				else if (worker == 0) {
                                    column += j;
                                    for (row = 0; row < 10; row++) {
						total += grades[row][column]; //total grades
					}
                                        printf("Chapter %d ,  HW %d Average: %0.2f\n", (i+1), (j+1), total/10.0);
					return 1;
                               }
                   }
              return 1;
              }
              column += hw;
    }
    return 0;
}
