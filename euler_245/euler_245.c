/******************************************************************************/
/*!
 * @file    euler_245.c
 * @brief   The problem statement is to find all numbers between 1 and N with 
 *          the reduced coresilience fraction having a numerator of 1. 
 *          Sum the numbers n between 1 and N with this property.
 *          
 *          Limit is N = 10^11
 *          Be really careful here, the sum could run over, or other 
 *          computations that bring about the possibilty of N^2, and 10^22 
 *          doesn't fit into 64 bits
 * 
 * @author  Cathal Harte
 *
 * @copyright   
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*******************************************************************************
* Definitions and types
*******************************************************************************/

// if the fraction can be reduced, do so recursively
// Don't waste space here, make it known that the values provided are
// operated on directly
struct primeList {
    int max_populated;
    int prime[10000000];
} primeList;

/*******************************************************************************
* Internal function prototypes
*******************************************************************************/

// A second consideration could be made to making a fraction-type struct
// if reduction occurred, return 1, otherwise return 0
int reduce_fraction(int *numerator, int *denominator);

// Self explanatory
void init_prime_list(int max_num);

// Self explanatory
int is_prime(int candidate);

// Calculate the Euler totient of a number - the number of fractions of a denominator
// which are resilient
int calc_euler_totient(int denom);

/*******************************************************************************
* Data
*******************************************************************************/

struct primeList prime_list;

/*******************************************************************************
* Functions
*******************************************************************************/

int main() {

    int N;
    int reducible_num, reducible_denom, euler_totient;

    scanf("%d",&N);
    init_prime_list(N);

    // What I mean by a static denom is one that shouldn't be passed by location to the 
    // reduce_fraction function
    int sum_of_set = 0;
    for(int static_denom = 2; static_denom<=N; static_denom++)
    {
        euler_totient = calc_euler_totient(static_denom);
        
        reducible_num = static_denom - euler_totient;
        reducible_denom = static_denom-1;
        reduce_fraction(&reducible_num, &reducible_denom);
        if(reducible_num == 1)
        {
            if(!is_prime(static_denom))
            {
                printf("nonprime in set!\n");
            }
            sum_of_set += static_denom;
        }
    }

    printf("%d\n", sum_of_set); 
    return 0;
}

int reduce_fraction(int *numerator, int *denominator)
{

    int fraction_reduced = 0;
    int max_prime_idx =  prime_list.max_populated;
    for(int prime_idx = 0; prime_idx < max_prime_idx; prime_idx++)
    {
        int divisor = prime_list.prime[prime_idx];

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

void init_prime_list(int max_num)
{
    prime_list.prime[0] = 2; // 1 is not technically a prime
    prime_list.max_populated = 1;
    for(int candidate = 3; candidate<=max_num; candidate++)
    {
        int is_divisible = 0;
        int max_prime_idx =  prime_list.max_populated;
        for(int prime_idx = 0; prime_idx < max_prime_idx; prime_idx++)
        {
            int divisor = prime_list.prime[prime_idx];
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
            prime_list.prime[max_prime_idx] = candidate;
            prime_list.max_populated = max_prime_idx+1;
        }
    }
}

int is_prime(int candidate)
{
    int is_prime = 0;
    int prime;
    int max_prime_idx =  prime_list.max_populated;
    for(int prime_idx = 0; prime_idx<max_prime_idx; prime_idx++)
    {
        prime = prime_list.prime[prime_idx];
        if (candidate == prime)
        {
            is_prime = 1;
            break;
        }
        else if (candidate > prime)
        {
            break;
        }
    }
}

int calc_euler_totient(int denom)
{
    static int reducible_num, reducible_denom;
    int euler_totient = 0;
    for(int num = 1; num < denom; num++)
    {
        // the reduce_fraction function acts directly on the address
        reducible_num = num;
        reducible_denom = denom;
        if(!reduce_fraction(&reducible_num, &reducible_denom))
        {
            euler_totient++;
        }
    }
    return euler_totient;
}