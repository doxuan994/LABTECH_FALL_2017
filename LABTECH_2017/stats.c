#include <stdio.h>
#define MAX_SIZE 256
/*
 * Class: CS 01205 - Computer Laboratory Techniques
 * Status: Complete and thoroughly tested
 * Comment: a program (in C) which reads in numbers from the keyboard,
 * one per line, until it gets a zero.
 * @author: Xuan Do
 * @version: 2017.09.12
 */
int main() {

    // Data fields
    int count  = 0;
    double sum    = 0;
    double min    = 0;
    double max    = 0;

    int badInputChecked = 0;
    int number = -1;
    char line[MAX_SIZE];
  
    printf("%% ./stats\n");
    
    // check if number is not 0 and valid storage size
    while( number != 0 && fgets(line, MAX_SIZE, stdin) != NULL ) {

        // Read formatted data from string
        badInputChecked = sscanf(line, "%d", &number);

        if ( badInputChecked == 1 && number != 0 ) {

            // count how many numbers are added
            count++;

            // check min & max
            if ( count == 1 ) {
                max = number;
                min = number;
            } else if ( number < min ) {
                min = number;
            } else if ( number > max ) {
                max = number;
            }

            // sum of numbers
            sum += number;
        }

        // check if input equals 0
        if ( badInputChecked == 0 ) {
            printf("Bad Input\n");
        }

    } 

    printf("# items:  %d\n", count);
    printf("Sum:  %lf\n", sum);
    printf("Max:  %lf\n", max);
    printf("Min:  %lf\n", min);
    printf("Mean: %lf\n", (sum / count) );

    return 0;

}
