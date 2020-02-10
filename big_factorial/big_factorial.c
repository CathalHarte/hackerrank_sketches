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

// Complete the extraLongFactorials function below.
// My initial idea is to take the power of 2 sums out of everything
// This allows me to perform lots of bitshifts to make it easier to
// compute the sum

// Actually it is much easier to check by using a 64 bit number if there has been a 
// 32b overflow
void extraLongFactorials(int n) {
    uint64_t overflow_allowed = 0;
    uint32_t enormous_int[14] = {1}; // God knows how big
    int highest_filled = 0;

    for(int factorial = 1; factorial<=n; factorial++)
    {
        if (factorial == 45)
        {
            printf("problem loop\n");
        }
        for(int enorm_idx = highest_filled; enorm_idx >= 0; enorm_idx--)
        {
            overflow_allowed = enormous_int[enorm_idx];
            overflow_allowed *= factorial;
            if(overflow_allowed > 100000000)
            {
                if(enorm_idx == highest_filled)
                {
                    highest_filled++;
                }
            }

            if (factorial == 45)
            {
                printf("%d\%100000000 = %d\n", overflow_allowed, overflow_allowed%100000000);
            }
            enormous_int[enorm_idx] = (uint32_t)(overflow_allowed%100000000);
            enormous_int[enorm_idx+1] += overflow_allowed/100000000;
        }
    }

    printf("%u", enormous_int[highest_filled]);
    for(int enorm_idx = highest_filled-1; enorm_idx >= 0; enorm_idx--)
    {
        printf("%08u", enormous_int[enorm_idx]);
    }
    printf("\n");
    printf("\n");
}

int main()
{
    extraLongFactorials(45);

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

// 11962222086548019456196316149565771506438423703040
// 119622220865480194561963161495657715064383733760000000000