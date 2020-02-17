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

uint64_t tally[10000000];

// Complete the arrayManipulation function below.

// Why on earth are they called queries? Isn't that fucking stupid?
uint64_t arrayManipulation(int n, int queries_rows, int queries_columns, uint64_t** queries) {

    uint64_t max = 0;
    uint64_t curr;
    int start, end;
    uint64_t *start_ptr, *end_ptr;
    for(int query_row = 0; query_row<queries_rows; query_row++)
    {
        start = queries[query_row][0]-1;
        start_ptr = &tally[start];
        end = queries[query_row][1];
        end_ptr = &tally[end];
        for(;start_ptr < end_ptr;start_ptr++) // idx starts at one in problem statement
        {
            curr = *start_ptr + (uint64_t)queries[query_row][2];
            *start_ptr = curr;
            if( curr > max)
            {
                max = curr;
            }
        }
    }

    // for(int tally_idx = 1; tally_idx < n; tally_idx++)
    // {   
    //     if (max < tally[tally_idx])
    //     {
    //         max = tally[tally_idx];
    //     }
    // }
    return max;
    // 7515267971
}

int main()
{
    FILE *fp = NULL;
    int n; // array length
    int m; // number of operations

    /* 1. Open file for Reading */                                                 
    if (NULL == (fp = fopen("../failing_test_case.tsv","r")))                                   
    {                                                                           
        perror("Error while opening the file.\n");                              
        exit(EXIT_FAILURE);                                                     
    }
    
    if (EOF == fscanf(fp, "%d %d", &n, &m))                                       
    { 
        printf("The file doesn't contain the necessary first line of information\n");
    }

    uint64_t row[3];

    int queries_rows = m;
    int queries_columns = 3;

    uint64_t** queries = malloc(m * sizeof(uint64_t*));

    // the technique used to achieve a 2D array here is nuts, so I'm going to see if I can learn it
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%lu %lu %lu", row, row+1, row+2);
        *(queries + i) = malloc(3 * (sizeof(uint64_t)));
        for (int j = 0; j < 3; j++) {
            *(*(queries + i) + j) = row[j];
        }
        if(i == m-1)
        {
            printf("%lu %lu %lu\n", *row, *(row+1), *(row+2));
        }
    }

    long result = arrayManipulation(n, m, 3, queries);

    printf("%lu\n", result);


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
