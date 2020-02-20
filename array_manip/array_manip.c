#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define TEN_MILLION     10000000
clock_t start_time, end_time;
double cpu_time_used;
     
char* readline();
char** split_string(char*);

uint64_t tally[TEN_MILLION];
uint64_t tally_2[TEN_MILLION];

typedef struct linked_range
{
    uint64_t val;
    uint64_t upprange; // upprange is the location of the first index in the array which is not "val"
} linked_range_t;

linked_range_t linked_range_array[TEN_MILLION];
linked_range_t linked_range_array_2[TEN_MILLION];

// Complete the arrayManipulation function below.

// The operations matrix is an m by 3 matrix
uint64_t arrayManipulation(int n, int operations_rows, int operations_columns, int** operations) 
{
    uint64_t max = 0;
    uint64_t addition;
    uint64_t *start_ptr, *end_ptr;

    start_time = clock();
    int ** last_operation_row = &(operations[operations_rows]);

    int operation_idx = 0;
    for(; operations<last_operation_row; operations++)
    {
        operation_idx++;
        start_ptr = tally + operations[0][0]-1;
        end_ptr = tally + operations[0][1];
        addition = operations[0][2];
        for(;start_ptr < end_ptr;) // idx starts at one in problem statement
        // We use idx zero, so although the operation is from say 1 to 5 inclusive, we
        // add up idxs 0 to 4, hence (< end_ptr)
        {
            *start_ptr++ += addition;
        }
    }

    end_time = clock();

    for(int tally_idx = 1; tally_idx < n; tally_idx++)
    {   
        if (max < tally[tally_idx])
        {
            max = tally[tally_idx];
        }
    }

    return max;
    // 7515267971
    // 2510535321
}

void init_linked_range_array(void)
{
    linked_range_array[0].upprange = TEN_MILLION;
}
// The operations matrix is an m by 3 matrix
// This is the linkedList style of solution
//      It can save on huge number of computations by having a data structure that defines ranges of values
uint64_t arrayManipulationLL(int n, int operations_rows, int operations_columns, int** operations) 
{
    uint64_t max = 0;
    uint64_t op_add;
    uint64_t op_lowrange, op_upprange;

    int lowrange_to_add;
    int upprange_to_add;
    int preexist_upprange;
    uint64_t preexist_val;

    start_time = clock();
    int ** last_operation_row = &(operations[operations_rows]);

    int operation_idx = 0;
    for(; operations<last_operation_row; operations++)
    {
        operation_idx++;

        op_lowrange = operations[0][0]-1;
        op_upprange = operations[0][1];
        op_add = operations[0][2];

        int linked_range_idx = 0;
        while(linked_range_idx < TEN_MILLION)
        {
            if(op_lowrange >= linked_range_array[linked_range_idx].upprange )
            {
                linked_range_idx = linked_range_array[linked_range_idx].upprange;
            }
            else
            {
                break;
            }
            
        }

        // the start val has been found
        // next we need to add subranges iteratively as necessary

        lowrange_to_add = op_lowrange;
        upprange_to_add = op_upprange;

        while(linked_range_idx < TEN_MILLION)
        {
            preexist_upprange = linked_range_array[linked_range_idx].upprange;
            preexist_val = linked_range_array[linked_range_idx].val;

            linked_range_array[lowrange_to_add].val = preexist_val + op_add;
            if(preexist_upprange > upprange_to_add)
            {
                linked_range_array[linked_range_idx].upprange = lowrange_to_add; // on a second loop, this value is overwritten
                linked_range_array[lowrange_to_add].upprange = upprange_to_add;
                linked_range_array[upprange_to_add].val = preexist_val;
                linked_range_array[upprange_to_add].upprange = preexist_upprange;

                break;
            }
            else if(preexist_upprange == upprange_to_add)
            {
                linked_range_array[linked_range_idx].upprange = lowrange_to_add; // on a second loop, this value is overwritten
                linked_range_array[lowrange_to_add].upprange = upprange_to_add;
                // And leave the next one untouched
                break;
            }
            else
            {
                if(lowrange_to_add == preexist_upprange)
                {
                    printf("Operation idx: %d\n", operation_idx);
                    printf("linked_range_array[%d].val:%lu .upprange: %ld\n", lowrange_to_add
                                                                         , linked_range_array[lowrange_to_add].val
                                                                         , linked_range_array[lowrange_to_add].upprange
                                                                         );
                    return 0;
                }
                linked_range_array[linked_range_idx].upprange = lowrange_to_add;
                linked_range_array[lowrange_to_add].upprange = preexist_upprange;
                lowrange_to_add = preexist_upprange;
                linked_range_idx = preexist_upprange;
            }
            
            
        }
    }

    end_time = clock();

    int linked_range_idx = 0;
    while(linked_range_idx < TEN_MILLION)
    {
        if(linked_range_array[linked_range_idx].val > max)
        {
            max = linked_range_array[linked_range_idx].val;
        }
        linked_range_idx = linked_range_array[linked_range_idx].upprange;
    }
    return max;
    // 7515267971
    // 2510535321
    // 144, for test case 4
}

void convert_linked_array_to_tally(void)
{
    int linked_range_idx = 0;
    while(linked_range_idx < TEN_MILLION)
    {
        int max_fill = linked_range_array[linked_range_idx].upprange;
        int val_fill = linked_range_array[linked_range_idx].val;
        for(int fill = linked_range_idx; fill < max_fill; fill++)
        {
            tally_2[fill] = val_fill;
        }
        linked_range_idx = max_fill;
    }
}

void convert_tally_to_linked_array(uint64_t *tally_ptr, linked_range_t *l_range)
{
    uint64_t curr_range_val = tally_ptr[0];
    l_range[0].val = tally_ptr[0];

    int l_range_idx = 0; // start at zero, we don't know how to populate .upprange yet
    uint64_t temp_tally_val = 0;
    
    int tally_idx = 0;
    for(tally_idx = 1;tally_idx < TEN_MILLION; tally_idx++)
    {
        temp_tally_val = tally_ptr[tally_idx];
        if(curr_range_val != temp_tally_val)
        {
            l_range[l_range_idx].val = curr_range_val;
            l_range[l_range_idx].upprange = tally_idx;
            l_range_idx = tally_idx;
            curr_range_val = temp_tally_val;
        }
    }
    l_range[l_range_idx].val = curr_range_val;
    l_range[l_range_idx].upprange = tally_idx;
}

void print_cpu_time_used(void)
{
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;   
    printf("CPU time used: %lf\n", cpu_time_used);
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

    int operations_rows = m;
    int operations_columns = 3;


    int** operations = malloc(m * sizeof(int*));

    // the technique used to achieve a 2D array here is nuts, so I'm going to see if I can learn it
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%lu %lu %lu", row, row+1, row+2);
        *(operations + i) = malloc(3 * (sizeof(int)));
        for (int j = 0; j < 3; j++) {
            *(*(operations + i) + j) = row[j];
        }
        if(i == m-1)
        {
            printf("%lu %lu %lu\n", *row, *(row+1), *(row+2));
        }
    }

    init_linked_range_array();
    long result = arrayManipulationLL(n, m, 3, operations);
    printf("Max value, according to the linked range algo: %ld\n", result);
    print_cpu_time_used();
    result = arrayManipulation(n, m, 3, operations);
    printf("Max value, according to the simple algo: %ld\n", result);
    print_cpu_time_used();


    convert_linked_array_to_tally();
    convert_tally_to_linked_array(tally, linked_range_array_2);

    // compare tallies
    int matches = 0;
    int ranges = 0;
    int l_range_idx = 0;
    for(l_range_idx = 0; l_range_idx < n;)
    {
        ranges++;
        if(linked_range_array[l_range_idx].upprange != linked_range_array_2[l_range_idx].upprange)
        {
            printf("Ranges are incorrect from idx %d, cannot continue making comparisons\n", l_range_idx);
            break;
        }
        if(linked_range_array[l_range_idx].val      == linked_range_array_2[l_range_idx].val)
        {
            matches++;
        }
        else {
            printf("Fail: %lu vs %lu\n", linked_range_array[l_range_idx].val, linked_range_array_2[l_range_idx].val);
        }
        l_range_idx = linked_range_array[l_range_idx].upprange;
    }
    printf("matches: %d/%d\n", matches, ranges);

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
