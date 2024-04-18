#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

/*This code is for reading and writing to files for the 2023-2024 COMP328 CA*/

/*Use the functions in this file to read from the input file, and write to the output file*/

/*You should use this file when compiling your code*/

/*Declare these functions at the top of each 'main' file*/

/*If there are any issues with this code, please contact: h.j.forbes@liverpool.ac.uk*/


int read_dims(char *filename);
double *read_array(char *filename, int numOfValues);
void *write_to_output_file(char *filename, double *output, int numOfValues);

/*Gets the number of the radiator temperatures in the file. Returns as a single integer*/
int read_dims(char *filename) {
    FILE *file = fopen(filename,"r");
    int i;
    
    if(file == NULL) {
        printf("Unable to open file: %s", filename);
        return -1; //-1 means error
    }

    char firstline[500];
    
    if(fgets(firstline, 500, file) == NULL){
        perror("Error reading file");
        return -1; //error
    }
    
    int line_length = strlen(firstline);
    
    int numOfValues;

    const char s[2] = " ";
    char *token;
    token = strtok(firstline, s);
    i = 0;
    while(token != NULL && i == 0) {
        numOfValues = atoi(token);
        i++;
        token = strtok(NULL, s);
    }
    fclose(file);
    return numOfValues;
}

/*Gets the data from the file. Returns as an array of doubles. Ignores the first numOfValues*/
double *read_array(char *filename, int numOfValues) {
    FILE *file = fopen(filename,"r");
    int i;
    
    if(file == NULL) {
        perror("Unable to open file: %s");
        return NULL; //error
    }

    char firstline[500];
    
    if(fgets(firstline, 500, file) == NULL){
        perror("Error reading file");
        return NULL; //error
    }

    //Ignore first line and move on since first line contains 
    //header information and we already have that. 

    double *one_d = malloc(sizeof(double) * numOfValues);
    
    for(i=0; i<numOfValues; i++) {
        if(fscanf(file, "%lf", &one_d[i]) == EOF){
            perror("Error reading file");
            return NULL; //error
        }
    }
    fclose(file);
    return one_d;
}

/*Writes to the output file*/
void *write_to_output_file(char *filename, double *output, int numOfValues){
    FILE *file = fopen(filename,"w");
    int i;
    
    printf("\nFile opened, writing dims\n");
    fprintf(file, "%d \n", numOfValues);
      
    printf("\nWriting output data\n");
    for(i=0; i < numOfValues; i++) {
        fprintf(file, "%.7lf ", output[i]);
    }
    fclose(file);
    return output;
}
