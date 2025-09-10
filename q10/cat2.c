#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{ 
    FILE *fp; 
    char ch; 

    if (argc < 2)  // No file argument given
    { 
        printf("File not entered\n"); 
        exit(1); 
    } 

    fp = fopen(argv[1], "r"); 
    if (fp == NULL)  // File not found
    { 
        printf("File does not exist\n"); 
        exit(1); 
    } 

    // Read and print file contents
    while ((ch = fgetc(fp)) != EOF) 
        printf("%c", ch);  

    fclose(fp); 
    printf("\n");   
    
    return 0; 
}
