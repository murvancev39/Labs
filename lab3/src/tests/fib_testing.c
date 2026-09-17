#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fib_heap.h"

unsigned *test_arr_generate (size_t size);

int main ()
{
    srand (42);
    long long time = 0;
    double res_time = 0;
    for (size_t i = 1000000; i <= 10000000; i += 1000000)
    {
        time = 0;
        
        for (int z = 0; z < 5; z++)
        {

            fib_heap heap = {};
            heap.min = NULL;
            
            unsigned *arr = test_arr_generate (i);
            
            time -= clock ();
            for (size_t k = 0; k < i; k++)
            {
                insert_val (&heap, arr [k], k);
            }
            time += clock ();
            
            destruct_nodes (heap.min);
            free (arr);
        }
        
        res_time = time;
        res_time /= 5;
        printf ("%lu %lf\n", i, res_time / CLOCKS_PER_SEC);
    }
    return 0;
}

unsigned *test_arr_generate (size_t size)
{
    unsigned *test_arr = (unsigned *) calloc (size, sizeof (int));
    for (size_t i = 0; i < size; i++)
    {
        test_arr [i] = rand ();
    }
    return test_arr;
}
