#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

long int tally[10000000];

// Complete the arrayManipulation function below.

// Why on earth are they called queries? Isn't that fucking stupid?
long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {

    for(int query_row = 0; query_row<queries_rows; query_row++)
    {
        for(int tally_idx = queries[query_row][0]-1;tally_idx < queries[query_row][1];tally_idx++) // idx starts at one in problem statement
        {
            tally[tally_idx] += queries[query_row][2];
        }
    }

    int max = tally[0];
    for(int tally_idx = 1; tally_idx < n; tally_idx++)
    {   
        if (max < tally[tally_idx])
        {
            max = tally[tally_idx];
        }
    }
    return max;
    // 7515267971
}

int main()
{
    FILE *fp = NULL;
    /* 1. Open file for Reading */                                                 
    if (NULL == (fp = fopen("file.txt","r")))                                   
    {                                                                           
        perror("Error while opening the file.\n");                              
        exit(EXIT_FAILURE);                                                     
    }
    
    
    int n = 11; // array length
    int m =  4; // number of operations



            // columns rows
    int test_array[4][3] = {{2, 6, 8},{3, 5, 7},{1, 8, 1},{5, 9, 15}};

    int queries_rows = m;
    int queries_columns = 3;

    int** queries = malloc(m * sizeof(int*));

    // the technique used to achieve a 2D array here is nuts, so I'm going to see if I can learn it
    for (int i = 0; i < m; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));
        for (int j = 0; j < 3; j++) {
            *(*(queries + i) + j) = test_array[i][j];
        }
    }

    char** queries_item_temp = split_string(readline());

    long result = arrayManipulation(n, 4, 3, queries);

    printf("%ld\n", result);


    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
