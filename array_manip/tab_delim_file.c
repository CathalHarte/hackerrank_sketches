// This file is a solution taken from stackoverflow
// https://stackoverflow.com/questions/27503904/read-tab-delimited-file-to-structure-in-c

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee
{
  char *empname;
  char *empid;
  int age;
  char *addr;

};

struct employee var;

#define SIZE 50 

int main(void)
{
    FILE *fp = NULL;                                                            
    int i = 0;                                                                  
    struct employee var = {NULL, NULL, 0, NULL};                                
    char line[SIZE] = {0}, *ptr = NULL;   

    /* 1. Open file for Reading */                                                 
    if (NULL == (fp = fopen("file.txt","r")))                                   
    {                                                                           
        perror("Error while opening the file.\n");                              
        exit(EXIT_FAILURE);                                                     
    }

    /* 2. Allocate Memory */                                                       
    var.empname = malloc(SIZE);                                                 
    var.empid = malloc(SIZE);                                                   
    var.addr = malloc(SIZE); 

    /* 3. Read each line from the file */   
    while (EOF != fscanf(fp, "%s", line))                                       
    {                                                                           
        /* 4. Tokenise the read line, using "\" delimiter*/                     
        ptr = strtok(line, "\\");                                                                                   
        var.empname = ptr;                                                      

        while (NULL != (ptr = strtok(NULL, "\\")))                              
        {                                                                       
            i++;                                                                

            /* 5. Store the tokens as per structure members , where (i==0) is first member and so on.. */
            if(i == 1)                                                          
                var.empid = ptr;                                                
            else if(i == 2)                                                     
                var.age = atoi(ptr);                                            
            else if (i == 3)                                                    
                var.addr = ptr;                                                 
        }                                                                       

        i = 0;        /* Reset value of i */                                                          
        printf("After Reading: Name:[%s] Id:[%s] Age:[%d] Addr:[%s]\n", var.empname, var.empid, var.age, var.addr);
    } 
}