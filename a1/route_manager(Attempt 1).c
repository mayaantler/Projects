/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Maya A.
 *
 */
#include <stdio.h>
#include <string.h>
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
    char DATA;
    char AIRLINE;
    char DEST_COUNTRY;
    char DEST_CITY;
    char SRC_CITY;
    char SRC_COUNTRY;
    int i = 0;
    char type[] = "";
    char value[] = "";

    
    
//loop through each string in the argv array
    while(argc > 1){
        char *cur = argv[argc];
        const char type;
        const char value;
        char *token;
    //figure out how to sscanf and separate the string into data type, and value
       int help = sscanf(cur,"%s", value);
    printf(help);
//Sort types into their local variables
      if(strcmp(type, "DATA") == 0){
            DATA = value;
        }else if(strcmp(type, "AIRLINE") == 0){
            AIRLINE = value;
        }else if(strcmp(type, 'DEST_COUNTRY') == 0){
            DEST_COUNTRY = value;
        }else if(strcmp(type, "DEST_CITY")==0){
            DEST_CITY = value;
        }else if(strcmp(type, 'SRC_CITY')==0){
            SRC_CITY = value;
        }else {
            SRC_COUNTRY = value;
        }

        argc--;
    }
    
    return 0;
}

//Function to read the contents of the file, and return a value containing the data
/*int read_file(const char filename) {
    char str[100];
    
    char filepointer = fopen(filename, 'r');
   
    fclose(filepointer);
    

    return 0;
}

//Function to take the data, and process it
int process_data() {

    return 1;
}
*/