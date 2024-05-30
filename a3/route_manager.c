/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
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
#include <string.h>
#include "list.h"


// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 80

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->word);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The head node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}




node_t *get_args(int argc, char*argv[]){

    char * token = strtok((argv[1]+2), "="); 
     token = strtok(NULL, " "); //Get Filename
    node_t * head = new_node(token);

    char * token2 = strtok((argv[2]+2), "=");
     token2 = strtok(NULL, " "); //Get Question
    node_t * node2 = new_node(token2);

    char * token3 = strtok((argv[3]+2), "=");
    token3 = strtok(NULL, " "); //Get N
    node_t * node3 = new_node(token3);
    
    head->next = node2;
    node2->next = node3; //Connect Nodes
    
    

    return head;
}

node_t * read_file(node_t* p){

    char *filename = p->word; //get the filename from the head node
    char buffer[MAX_LINE_LEN]; //buffer to store data from each line

    char temp[500]; //temporary string to store data together
    FILE* fp;
    int count = 0;
    fp = fopen(filename, "r"); //open the file

    fgets(buffer, MAX_LINE_LEN, fp); //strip off routes:

    while(count < 13){
        fgets(buffer, MAX_LINE_LEN, fp); //get each line of data

        if(count == 0){//format line at the start of block
            strcpy(&buffer[0], &buffer[1]); //strip off the -
        }

        strcat(temp, buffer); //add data in buffer to the temporary string
        
        count +=1;
    }

    node_t * head = new_node(temp); //Create head node

    node_t * node_ptr = head;


    while(fgets(buffer, MAX_LINE_LEN, fp)!= NULL){
        count = 1;
        strcpy(temp, "");
       
        strcat(temp, buffer);
        
        while(count < 13){ //create a node for each block

            fgets(buffer, MAX_LINE_LEN, fp);
            
           
            strcat(temp, buffer);
            count +=1;

        }

        node_t * cur = new_node(temp);
        node_ptr->next = cur;
        node_ptr = cur;
    }

    
    
    fclose(fp);
    return head;
    
}

node_t * sort_flights(int Q, node_t* list){
    node_t * temp = list;
    node_t * result = NULL; //head node for the return list

    while(temp != NULL){ //Iterate through the linked list

        char temp_str[500];

        if(Q == 1){
            //SORT OUT TOP N AIRLINES WITH DEST COUNTRY AS CANADA
            strcpy(temp_str, temp->word);
            
            char * token = strtok(temp_str, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n"); //Get the Dest Country portion of the string

            strcpy(temp_str, token);

            token = strtok(temp_str, ":");
            token = strtok(NULL, "\n");
            token++;
            
            if(strcmp(token, "Canada")==0){
                
                if(result == NULL){
                    node_t * cur = new_node(temp->word);
                    result = add_front(result, cur);
                    
                    
                }else{
                    node_t * cur = new_node(temp->word);
                    result = add_inorder(result, cur);
                    
                }
            }
        }else if(Q == 2){
            //SORT OUT TOP N LEAST POPULAR COUNTRIES
            strcpy(temp_str, temp->word);
            
            char * token = strtok(temp_str, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n"); //Get the Dest Country portion of the string

            strcpy(temp_str, token);

            token = strtok(temp_str, ":");
            token = strtok(NULL, "\n");

            if(token[1] == '\''){ //strip off any wrong input
                token +=2;
                token[strlen(token)-1] = '\0';
            }
            

            token++;
            if(result == NULL){
                node_t * cur = new_node(token);
                result = add_front(result, cur);
            }else{
                    node_t * cur = new_node(token);
                    result = add_inorder(result, cur);
                }
        }else{
            //SORT OUT TOP N DESTINATION AIRPORTS

            strcpy(temp_str, temp->word);
            
            char * token = strtok(temp_str, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
            token = strtok(NULL, "\n");
             //Get the Dest Airport portion of the string
             strcpy(temp_str, token);

            token = strtok(temp_str, ":");
            token = strtok(NULL, "\n");

            if(token[1] == '\'' || token[1] == '\"'){ //strip off any wrong input
                token +=2;
                token[strlen(token)-1] = '\0';
                
            }else{ //get rid of space if output is correct
                token++;
                
            }
            if(result == NULL){
                    node_t * cur = new_node(temp->word);
                    result = add_front(result, cur);
                    
                    
                }else{
                    node_t * cur = new_node(temp->word);
                    result = add_inorder(result, cur);
                    
                }
        }
        

        temp = temp->next;
    }
    
    return result;
}

void csv_format(node_t* list, int N, int Q){
    node_t * temp = list;
    char tempstr[500];
    
    char *final;

    if(Q == 1){

        while(temp != NULL){
        final = (char*)malloc(50 * sizeof(char));
        strcpy(tempstr, temp->word);
        
        char * token = strtok(tempstr, "\n");
        token += 16; //get airline name
        
        strcpy(final, token); //add airline name to final string
        token = strtok(NULL, "\n");
        token += 28;
        
        strcat(final, " (");
        strcat(final, token); //add airline code + format with brackets
        strcat(final, ")");

        temp->word = final; //modify the temp->word
        
        temp = temp->next;
        }
        
    }else if(Q == 3){
        while(temp != NULL){
        final = (char*)malloc(75 * sizeof(char));
        strcpy(tempstr, temp->word);
        
        char * token = strtok(tempstr, "\n");

    
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n");
        token = strtok(NULL, "\n"); //dest airport name
        char * token2 = strtok(NULL, "\n"); //city
        char * token3 = strtok(NULL, "\n"); //country
        char * token4 = strtok(NULL, "\n"); //code
        
        token +=19; //get destination airport name
        token2 +=19; //get destination airport city
        token3 +=22; //get destination airport country
        token4 += 31; //get airport code
        
        strcat(final, token); //add to final string
        strcat(final, " (");
        strcat(final, token4);
        strcat(final, "), ");
        strcat(final, token2);
        strcat(final, ", ");
        strcat(final, token3);
            
        
        temp->word = final; //modify the temp->word
        temp = temp->next;
        
       
        }

    }
}

void results_to_csv(node_t * list, int Q, int N){
    char buffer[100];
    int i = 0;
    FILE *fp;
    
    if(Q==1){ //Create q1.csv
    fp = fopen("output.csv", "w+");
    fputs("subject, statistic\n", fp);
    while(i < N){


             //Write to file
            fputs(list->word, fp);
            fputs("\n", fp);
            list = list->next;

        i++;
    }

    }else if(Q==2){
        fp = fopen("output.csv", "w+");
        fputs("subject, statistic\n", fp);
        while(i < N){

       

             //Write to file
            fputs(list->word, fp);
            fputs("\n", fp);
            list = list->next;

        
        
        

        i++;
    }
        
    }else{
        fp = fopen("output.csv", "w+");
        fputs("subject,statistic\n", fp);
         while(i < N){
            
            strcpy(buffer, list->word);
            
            char * subject = strtok(buffer, ":"); //get NAME (CODE), CITY, COUNTRY into buffer
            char * statistic = strtok(NULL, "");
            
            
            
             //Write to file
             fputs("\"", fp);
            fputs(subject, fp);
             fputs("\"", fp);
             fputs(",", fp);
             fputs(statistic, fp);
             fputs("\n", fp);

             

            list = list->next;
        
        

        i++;
    }
    fclose(fp);
    
}
}

node_t * freq(node_t * list, int num, int Q){
    
    char * name;
    char  number[4];
    node_t * result = list;
    

     //adjust the start node depending on how many times the function has been executed
        
        if(num == 1){
            result = result->next;
        }
     

    int count = 0;
    name = result->word;
    while(result->next != NULL && strcmp(result->word, result->next->word)==0){
        result = remove_front(result);
        count ++;
    }
    count ++;
    sprintf(number, "%d", count);
   if(Q!=3){
     strcat(name, ",");
   }else{
    strcat(name, ":");
   }
       
    
    
    strcat(name, number);
    result->word = name;
    

    
    return result;

}

node_t * freq3(node_t * list, int num, int Q){
    
    char * name;
    char  number[4];
    node_t * result = list;
    

     //adjust the start node depending on how many times the function has been executed
        
        if(num == 1){
            result = result->next;
        }
     

    int count = 0;
    name = result->word;
    while(result->next != NULL){
        if( strcmp(result->word, result->next->word)==0){
            result = remove_front(result);
            count ++;
        }
        result = result->next;
    }
    count ++;
    sprintf(number, "%d", count);
   
        strcat(name, ":");
    
    
    strcat(name, number);
    result->word = name;
    

    
    return result;

}

node_t * sort_ascending_rec3( node_t* head, node_t * tail){
    // Get head node of given linked list
    node_t * cur = head;
    node_t * cur2 = head;
    char buffer[100];
    char buffer2[100];
    
    

    char * temp;
    while (cur2 != NULL && cur2 != tail) {
        strcpy(buffer, cur2->word);
        strcpy(buffer2, tail->word);
        char * token = strtok(buffer, ":");
        token = strtok(NULL, "");//Get the number

        char * token2 = strtok(buffer2, ":");
        token2 = strtok(NULL, "");
        if (atoi(token) > atoi(token2)) {
            cur = head;
  
            // Swapping  node values
            temp = head->word;
            head->word= cur2->word;
            cur2->word = temp;
  
            // Visiting the next node
            head = head->next;
        }
  
        // Visiting the next node
        cur2 = cur2->next;
    }
  
    // Change tail node value to current node
    temp = head->word;
    head->word= tail->word;
    tail->word = temp;
    
    return cur;
}

node_t * sort_ascending_rec( node_t* head, node_t * tail){

    // set temp nodes
    node_t * cur = head;
    node_t * cur2 = head;
    char buffer[100];
    char buffer2[100];
    
    char * temp;


    while (cur2 != NULL && cur2 != tail) {
        strcpy(buffer, cur2->word);
        strcpy(buffer2, tail->word);
        char * token = strtok(buffer, ",");
        token = strtok(NULL, "");// Get the digit value out of the string

        char * token2 = strtok(buffer2, ",");
        token2 = strtok(NULL, "");
        if (atoi(token) > atoi(token2)) {
            cur = head;
  
            
            temp = head->word;
            head->word= cur2->word;
            cur2->word = temp;
  
        
            head = head->next;
        }
  

        cur2 = cur2->next;
    }
  
    // Change tail node value to current node
    temp = head->word;
    head->word= tail->word;
    tail->word = temp;
    return cur;
}

node_t * sort_desc_rec( node_t* head, node_t * tail)
{
    // Get head node of given linked list
    node_t * cur = head;
    node_t * cur2 = head;
    char buffer[100];
    char buffer2[100];

    char * temp;
    while (cur2 != NULL && cur2 != tail) {
        strcpy(buffer, cur2->word);
        strcpy(buffer2, tail->word);
        char * token = strtok(buffer, ",");
        token = strtok(NULL, "");//Get the number

        char * token2 = strtok(buffer2, ",");
        token2 = strtok(NULL, "");
        if (atoi(token) < atoi(token2)) {
            cur = head;
            
            temp = head->word;
            head->word= cur2->word;
            cur2->word = temp;
  
            head = head->next;
        }
        cur2 = cur2->next;
    }
  
    // Change tail node value to current node
    temp = head->word;
    head->word= tail->word;
    tail->word = temp;
    return cur;
}

 void sort_ascending(node_t * head, node_t * tail){

    if (head == tail || head == NULL) { //base case, return when end of list is reached or when head node equals tail node
        return;
    }else{
     node_t* p = sort_ascending_rec(head, tail);
  
    if (p != NULL && p->next != NULL) {
        sort_ascending(p->next, tail);
    }
    if (p != NULL && head != p) {
        sort_ascending(head, p);
    }
    }
}

 void sort_ascending3(node_t * head, node_t * tail){

    if (head == tail || head == NULL) { //base case, return when end of list is reached
        return;
    }else{
     node_t* p = sort_ascending_rec3(head, tail); //recursive call to sort and swap nodes
  
    if (p != NULL && p->next != NULL) {
        sort_ascending3(p->next, tail);
    }
    if (p != NULL && head != p) {
        sort_ascending3(head, p);
    }
    }
}

void sort_descending(node_t * head, node_t * tail){

    if (head == tail || head == NULL) { //base case, return when end of list is reached
        return;


    }else{ //base case not reached

     node_t* p = sort_desc_rec(head, tail); //call recursion
  
    if (p != NULL && p->next != NULL) { 
        sort_descending(p->next, tail); //sort and swap nodes
    }
  
    if (head != p && p != NULL) {
        sort_descending(head, p); //sort and swap nodes
    }
    }

}

void alphabetical(node_t* list){
    node_t * in = list;
    node_t * n = in->next;
    char * temp;
    char buffer[100];
    char buffer2[100];

    while(n != NULL){
        strcpy(buffer, n->word);
        strcpy(buffer2, in->word);

        char * token = strtok(buffer, ",");
        token = strtok(NULL, "");

        char * token2 = strtok(buffer2, ",");
        token2 = strtok(NULL, "");

        if(strcmp(token, token2)==0 && strcmp(buffer2, buffer)>0){ //if the numbers are the same and the head string is not alphabetically sorted
        //swap the two nodes
        temp = n->word;
        n->word = in->word;
        in->word = temp;

        }

        
        
        in = n;
        n = n->next;
    }

    
}
/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{

    //Get input from command line
    node_t * args = get_args(argc, argv); //List contains Filename -> Question -> N
    
    //Read the file, store data in a linked list, with each node containing the info for one flight
    node_t * Flights = read_file(args);
    
   //Sort the Data according to the question
    node_t * sorted = sort_flights(atoi(args->next->word), Flights);
   

    
    csv_format(sorted, atoi(args->next->next->word), atoi(args->next->word)); //format data correctly, arrange in order
    
    //Count Instances
    node_t * final = NULL;
    node_t * result = NULL;
    if(atoi(args->next->word)!=3){


    sorted = freq(sorted, 0, atoi(args->next->word));
    node_t * temp = peek_front(sorted);
     final = new_node(temp->word);

        while (sorted->next != NULL){ //Loop through sorted list
        
            sorted = freq(sorted, 1, atoi(args->next->word));
            temp = peek_front(sorted);
            temp = new_node(temp->word);
            final = add_inorder(final, temp);
    
        }
    }else{
        
        node_t * t = peek_front(sorted); //get the head node
        node_t * c = new_node(t->word); //create a new node with the data of the head
        result = add_inorder(result, c);
        sorted = remove_front(sorted); //remove the node from the original list

        while(sorted != NULL){
            t = peek_front(sorted); 
            c = new_node(t->word);
            result = add_inorder(result, c);
            sorted = remove_front(sorted);
            
        }
        result = freq(result, 0, atoi(args->next->word));
        t = peek_front(result);
        final = new_node(t->word);

        while(result->next != NULL){
             result =  freq(result, 1, atoi(args->next->word));
             t = peek_front(result);
             t = new_node(t->word);
             final = add_inorder(final, t);
        }     

    }

   
    node_t * temp5 = final;
    if(atoi(args->next->word) != 2){ //Only do this when getting the top N things
            
            while(temp5->next!= NULL){
                temp5 = temp5->next; //get the tail node
            }
            if(atoi(args->next->word) == 1){
                sort_ascending(final, temp5);
            }else{
                sort_ascending3(final, temp5);
            }
       
        
        }
    else{
        while(temp5->next!= NULL){
                temp5 = temp5->next; //get the tail node
            }
            sort_descending(final, temp5);
        
    }
   
    
    
    node_t * t = final;
    while(t != NULL){
        alphabetical(final); //Ensure results are arranged alphabetically
        t = t->next;
    }
    
    
    
   //Output Data
   
   results_to_csv(final, atoi(args->next->word), atoi(args->next->next->word));

    
    free(args); //free the memory that was used for the args list
    free(Flights); //free the memory that was used for the Flights list
    free(sorted); //free
    
    exit(0);
    
}
