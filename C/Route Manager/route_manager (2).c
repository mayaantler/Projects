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
struct Flight {
    char Airline_Name[50];
    char Airline_Code[10];
    char Airline_Country[30];
    char From_Airport_Name[50];
    char From_Airport_City[50];
    char From_Airport_Country[50];
    char From_Airport_Code[10];
    int From_Altitude;
    char To_Airport_Name[50];
    char To_Airport_City[50];
    char To_Airport_Country[50];
    char To_Airport_Code[50];
    int To_Altitude;
};


/*
int print_result(const char *flights){
    FILE *fp;
            fp = fopen("output.txt", "w");
            fputs("NO RESULTS FOUND.\n", fp);
            fclose(fp);

            return(0);
}
*/

 char * split_lines(char * line, char flight_info[]){
    int i;

    char * temp[13];

//set first value in the temp array
    char * token = strtok(line, ",");
    temp[0] = token;

//split the rest of the lines 
    for(i = 1, i < 13, i++){
       char * cur = strtok(NULL, ",");
       if(cur==NULL){
        temp[i] = "filler";
       }else{
        temp[i] = cur;
       }
    }

        return flight_info;
    }
    
    

 char* read_file(char * filename, char * airline, char * dest_country, char * dest_city, char * src_city, char * src_country, char flight_info[]){
    
    FILE* ptr;
    char buffer[500];
    char * str;
    int num = 0;
    ptr = fopen(filename, "r");
    
    fgets(buffer, 500, ptr);//remove file header

    while(fgets(buffer,500,ptr)!=NULL){ //Reads file line by line, loop stops when there are no more lines
        
       str = split_lines(buffer, flight_info);
       printf("%s", str);
    }
    fclose(ptr);
    return flight_info;
    
}

int main(int argc, char *argv[])
{
    
            int i=1;
           
            char * filename;
            char * airline;
            char * dest_country;
            char * dest_city;
            char * src_city;
            char * src_country;
            char  flight_info[200];
            const char * flights;
             
            
            
        while(i < argc){ //Loop through arguments, assign their values to local variables
           

            char * first_line = argv[i] +=2; //strip -- off of input
            
            char * token = strtok(first_line, "=");
            
            char * data_type = token; //DATA TYPE STORED AS A STRING
            char * token2 = strtok(NULL, "");
            
            char * value = token2; //DATA VALUE STORED AS A STRING

            //Sort values according to their data type, and define them as local variables
            if(strcmp(data_type, "DATA")==0){
                filename = value;
                
            }else if(strcmp(data_type, "AIRLINE")==0){
                airline = value;

            }else if(strcmp(data_type, "DEST_COUNTRY")==0){
                dest_country = value;
                
            }else if(strcmp(data_type, "DEST_CITY")==0){
                dest_city = value;
                
            }else if(strcmp(data_type, "SRC_CITY")==0){
                src_city = value;
                
            }else if(strcmp(data_type, "SRC_COUNTRY")==0){
                src_country = value;
                
            }

            
            i+=1;
        }
        
        

        flights = read_file(filename, airline, dest_country, dest_city, src_city, src_country, flight_info);
        
        //print_result(flights);

    exit(0);
}





