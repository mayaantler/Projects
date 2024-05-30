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

 void split_lines(char * line, char flight_info[], char important[], int type){
    int i;

    char * temp[13];

//set first value in the temp array
    char * token = strtok(line, ",");
    temp[0] = token;

//split the rest of the lines 
    for(i = 1; i < 13; i++){
       char * cur = strtok(NULL, ",");
       if(cur==NULL){
        temp[i] = "filler";
       }else{
        temp[i] = cur;
       }
    }

    //add flight data to flight_info array
    strcat(flight_info, temp[0]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[1]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[2]);
    strcat(flight_info, ",");
     strcat(flight_info, temp[3]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[4]);
    strcat(flight_info, ",");
     strcat(flight_info, temp[5]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[6]);
    strcat(flight_info, ",");
     strcat(flight_info, temp[7]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[8]);
    strcat(flight_info, ",");
     strcat(flight_info, temp[9]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[10]);
    strcat(flight_info, ",");
     strcat(flight_info, temp[11]);
    strcat(flight_info, ",");
    strcat(flight_info, temp[12]);

    if(type == 4){
        strcat(important, temp[1]);
        strcat(important, ",");
        strcat(important, temp[10]);
    }

    }
    
    

 void read_file(char * filename, char * airline, char * dest_country, char * dest_city, char * src_city, char * src_country, int argc){
    char important[100];
    char flight_info[200];
    const char empty[200] = "";
    FILE* ptr;
    char buffer[500];
    char * str;
    int num = 0;
    ptr = fopen(filename, "r");
    
    fgets(buffer, 500, ptr);//remove file header
    
    while(fgets(buffer,500,ptr)!=NULL){ //Reads file line by line, loop stops when there are no more lines
        
    split_lines(buffer, flight_info, important, argc);

    char * token = strtok(important, ",");
    char* token2 = strtok(NULL, ",");
    if((strcmp(token, airline)==0)&&(strcmp(token2, dest_country)==0)){
        printf("%s", "FLIGHT MATCHED\n");

    }
    strcpy(important, empty);
    strcpy(flight_info, empty);
    


    }
    fclose(ptr);

    //return flight_info;
    
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
           // char  flight_info[200];
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
        
        

        read_file(filename, airline, dest_country, dest_city, src_city, src_country, argc);
        
        //print_result(flights);

    exit(0);
}





