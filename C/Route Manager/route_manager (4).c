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



void print_result(char  flights[], int c, char * airline_name ,char * airline,char * dest_country,char * dest_city, char *src_city,char * src_country){
    char str[100] = "FLIGHTS";
    FILE *fp;

    fp = fopen("output.txt", "w");

    if(flights && c == 4 && (strlen(flights)>1)){

        strcat(str, " TO ");
        strcat(str, dest_country);
        strcat(str, " BY ");
        strcat(str, airline_name);
        strcat(str, " (");
        strcat(str, airline);
        strcat(str, "):\n");

        fputs(str, fp);
        fputs(flights, fp);
        


        
    }else if(flights && c == 5 && (strlen(flights)>1)){

        strcat(str, " FROM ");
        strcat(str, src_country);
        strcat(str, " TO ");
        strcat(str, dest_city);
        strcat(str, ", ");
        strcat(str, dest_country);
        strcat(str, ":\n");

        fputs(str, fp);
        fputs(flights, fp);

    }else if(flights && c == 6 && (strlen(flights)>1)){

        strcat(str, " FROM ");
        strcat(str, src_city);
        strcat(str, ", ");
        strcat(str, src_country);
        strcat(str, " TO ");
        strcat(str, dest_city);
        strcat(str, ", ");
        strcat(str, dest_country);
        strcat(str, ":\n");

        fputs(str, fp);
        fputs(flights, fp);

    }else{

        fputs("NO RESULTS FOUND.\n", fp);
    }
    
                fclose(fp);



}

 void split_lines(char buffer[], char * vals[]){

    int i = 0;

    char * token = strtok(buffer, ",");

    vals[i] = token;
    for(i =1; i < 13; i++){

        char * token2 = strtok(NULL, ",");

        if(token2 == NULL){
            vals[i] = "filler";
        }else{
            vals[i] = token2;
        }

    }
    
}

int sort_flight(char * str[],  char * airline, char * dest_country, char *dest_city, char * src_city, char *src_country){

    if((airline && (strcmp(str[1], airline)==0) && (strcmp(str[10], dest_country)==0))){
        return 1;
    }else if(src_country&& dest_city && !src_city && (strcmp(str[5], src_country)==0)&&(strcmp(str[9],dest_city)==0)&&(strcmp(str[10],dest_country)==0)){
        return 2;
    }else if(src_city && dest_city &&(strcmp(str[4],src_city)==0)&&(strcmp(str[5], src_country)==0) &&((strcmp(str[9], dest_city))==0)
    && (strcmp(str[10], dest_country)==0)){
        return 3;
    }else{
        return 0;
    }
    
    
}

void read_lines(char * filename, char flights[],char airline_name[], char * airline, char * dest_country, char *dest_city, char * src_city, char *src_country){

    char buffer[500];
    int result = 0;
    int i;
    
    char * vals[13];

    FILE * fp = fopen(filename, "r");

    fgets(buffer, 500, fp);

    while(fgets(buffer, 500, fp)!=NULL){

        
        split_lines(buffer, vals); //split lines, store data in array

        result = sort_flight(vals, airline, dest_country, dest_city, src_city, src_country); //check if flight is a match
        

    if(result == 1){
        strcat(airline_name, vals[0]);
        strcat(airline_name, ",");
        
        strcat(flights, "FROM: ");
        strcat(flights, vals[6]);
        strcat(flights, ", ");
        strcat(flights, vals[4]);
        strcat(flights, ", ");
        strcat(flights, vals[5]);
        strcat(flights, " TO: ");
        strcat(flights, vals[8]);
        strcat(flights, " (");
        strcat(flights, vals[11]);
        strcat(flights, "), ");
        strcat(flights, vals[9]);
        strcat(flights, "\n");
        
    }else if(result == 2){
        strcat(airline_name, vals[0]);
        strcat(airline_name, ",");

        strcat(flights, "AIRLINE: ");
        strcat(flights, vals[0]);
        strcat(flights, " (");
        strcat(flights, vals[1]);
        strcat(flights, ") ORIGIN: ");
        strcat(flights, vals[3]);
        strcat(flights, " (");
        strcat(flights, vals[6]);
        strcat(flights, "), ");
        strcat(flights, vals[4]);
        strcat(flights, "\n");

    }else if(result ==3){
        
        
        strcat(airline_name, vals[0]);
        strcat(airline_name, ",");

        strcat(flights, "AIRLINE: ");
        strcat(flights, vals[0]);
        strcat(flights, " (");
        strcat(flights, vals[1]);
        strcat(flights, ") ROUTE: ");
        strcat(flights, vals[6]);
        strcat(flights, "-");
        strcat(flights, vals[11]);
        strcat(flights, "\n");
    
    }
        
    }
    
    
    
}

int main(int argc, char *argv[])
{
    
            int i=1;
           
            char airline_name[50];
            char * filename;
            char * airline;
            char * dest_country;
            char * dest_city;
            char * src_city;
            char * src_country;
            char  flights[500];
            
            
            
             
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
        
    
        read_lines(filename, flights, airline_name, airline, dest_country, dest_city, src_city, src_country);
        //now we have all flights stored in a string
            
            char copy[50];
            char * token3 = strtok(airline_name, ",");
            if(token3){
            
            strcpy(copy, token3);
            
            } //for use case 1, copies airline name into a usable string

       
        
        
        
        
        //write results to output.txt
        print_result(flights, argc, copy, airline, dest_country, dest_city, src_city, src_country);

    
}