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
// if reduction occurred, return 1, otherwise return 0
int reduce_fraction(int *numerator, int *denominator, struct primeList *p_list);

struct primeList prime_list;

void create_prime_list(struct primeList* p_list, int max_num);


// The problem statement is to find all numbers between 1 and N with the reduced coresilience fraction having a numerator of 1
// Sum the numbers n between 1 and N with this property

// Limit is N = 10^11
// Be really careful here, the sum could run over, or other computations that bring about the possibilty of N^2, and 10^22 doesn't
// fit into 64 bits
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    // Who cares?
    int N = 5;
    int reducible_num, reducible_denom;

    create_prime_list(&prime_list, N);

    // What I mean by a static denom is one that shouldn't be passed by location to the 
    // reduce_fraction function
    int sum_of_set = 0;
    for(int static_denom = 2; static_denom<=N; static_denom++)
    {
        int num_indivisible_fractions = 0;
        for(int static_num = 1; static_num < static_denom; static_num++)
        {
            reducible_num = static_num;
            reducible_denom = static_denom;
            if(!reduce_fraction(&reducible_num, &reducible_denom, &prime_list))
            {
                num_indivisible_fractions++;
            }
        }
        reducible_num = static_denom - num_indivisible_fractions;
        reducible_denom = static_denom-1;
        reduce_fraction(&reducible_num, &reducible_denom, &prime_list);
        if(reducible_num == 1)
        {
            sum_of_set += static_denom;
        }
    }

    printf("%d, \n", sum_of_set);
    // for( int i = 0; i<prime_list.max_populated; i++)
    // {
    //     printf("%d, ", prime_list.prime[i]);
    // }
    // reduce_fraction(&num,&denom, &prime_list);
    // printf("%d/%d\n", num, denom);    
    return 0;
}

int reduce_fraction(int *numerator, int *denominator, struct primeList *p_list)
{

    int fraction_reduced = 0;
    int max_prime_idx =  p_list->max_populated;
    for(int prime_idx = 0; prime_idx < max_prime_idx; prime_idx++)
    {
        int divisor = p_list->prime[prime_idx];

        // Start with checking the numerator, it is guaranteed to be smaller, so we save time
        if( divisor*divisor > *denominator)
        {
            break; // it's game over
        }
        if(!(*numerator % divisor)) // if the numerator can be simplified
        {
            if(!(*denominator % divisor)) // and so can the denominator be
            {
                // then we can simplify the fraction
                fraction_reduced = 1;
                *numerator   /= divisor;
                *denominator /= divisor;

                // hacky, lazy style, just so you know
                // we're going to subtract 1 from the prime_idx, so that we retry the current value
                // next loop, until the prime cannot fit any more times.
                prime_idx--;
            }
        }
    }
    return fraction_reduced;
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
