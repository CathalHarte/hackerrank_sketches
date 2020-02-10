#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// if the fraction can be reduced, do so recursively
// Don't waste space here, make it known that the values provided are
// operated on directly
struct primeList {
    int max_populated;
    int prime[10000000];
} primeList;


// A second consideration could be made to making a fraction-type struct
void reduce_fraction(int *numerator, int *denominator, struct primeList *p_list);

struct primeList prime_list;

void create_prime_list(struct primeList* p_list, int max_num);

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    // Who cares?
    int num = 8;
    int denom = 12;

    create_prime_list(&prime_list, 300);

    for( int i = 0; i<prime_list.max_populated; i++)
    {
        printf("%d, ", prime_list.prime[i]);
    }
    reduce_fraction(&num,&denom, &prime_list);
    printf("%d/%d\n", num, denom);    
    return 0;
}

void reduce_fraction(int *numerator, int *denominator, struct primeList *p_list)
{

    int max_prime_idx =  p_list->max_populated;
    for(int prime_idx = 0; prime_idx < max_prime_idx; prime_idx++)
    {
        int divisor = p_list->prime[prime_idx];

        // Start with checking the numerator, it is guaranteed to be smaller, so we save time
        if( divisor*divisor > *numerator)
        {
            break; // it's game over
        }
        if(!(*numerator % divisor)) // if the numerator can be simplified
        {
            if(!(*denominator % divisor)) // and so can the denominator be
            {
                // then we can simplify the fraction
                *numerator   /= divisor;
                *denominator /= divisor;

                // hacky, lazy style, just so you know
                // we're going to subtract 1 from the prime_idx, so that we retry the current value
                // next loop, until the prime cannot fit any more times.
                prime_idx--;
            }
        }
    }
}

void create_prime_list(struct primeList *p_list, int max_num)
{
    p_list->prime[0] = 2; // 1 is not technically a prime
    p_list->max_populated = 1;
    for(int candidate = 3; candidate<=max_num; candidate++)
    {
        int is_divisible = 0;
        int max_prime_idx =  p_list->max_populated;
        for(int prime_idx = 0; prime_idx < max_prime_idx; prime_idx++)
        {
            int divisor = p_list->prime[prime_idx];
            if (divisor*divisor > candidate)
            {
                break;
            }
            if(!(candidate % divisor))
            {
                is_divisible = 1;
                break;
            }
        }
        if(!is_divisible)
        {
            p_list->prime[max_prime_idx] = candidate;
            p_list->max_populated = max_prime_idx+1;
        }
    }
}
