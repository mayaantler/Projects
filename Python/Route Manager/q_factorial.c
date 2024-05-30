/** @file q_array_rotate.c
 *  @brief Submission program for Lab 04.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Maya A.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{

        // variable to store the final answer
        int factorial = 1;
        int num;
        int i = 1;

        // WRITE YOUR CODE TO DO COMMAND LINE INPUT CHECKING HERE

        if(argv[1] < 0){ //make sure number is not negative
                return 1;
        }
        // Takes the command line input and converts it into int.
        num = atoi(argv[1]);

        while(i != num){
                factorial *= (num -i);

                i++;

        }
        factorial *= num;

        // WRITE YOUR CODE TO DO THE FACTORIAL CALCULATIONS HERE

        printf("%d\n", factorial);
        return 0;
}
