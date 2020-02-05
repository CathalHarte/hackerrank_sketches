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
    uint64_t overflow_check_mask = 0xffffffff00000000;
    uint32_t enormous_int[10] = {1}; // God knows how big
    int highest_32b_filled = 0;

    for(int factorial = 1; factorial<=n; factorial++)
    {
        for(int enorm_idx = highest_32b_filled; enorm_idx >= 0; enorm_idx--)
        {
            overflow_allowed = enormous_int[enorm_idx];
            overflow_allowed *= factorial;
            if(overflow_allowed & overflow_check_mask)
            {
                if(enorm_idx == highest_32b_filled)
                {
                    highest_32b_filled++;
                }
            }
            enormous_int[enorm_idx] = (uint32_t)overflow_allowed;
            enormous_int[enorm_idx+1] += (uint32_t)(overflow_allowed >> 32);
        }
    }
    // ok, so now the number is stored correctly, but how will I print it as a decimal number?
    printf("%ld\n", ((uint64_t)enormous_int[1] << 32) + enormous_int[0]);
}

int main()
{
    extraLongFactorials(14);

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
