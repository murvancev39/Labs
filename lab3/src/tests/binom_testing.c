#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binom_heap.h"

unsigned *test_arr_generate (size_t size);

int main ()
{    
    long long time = 0;
    double res_time = 0;
    for (size_t i = 1000000; i <= 10000000; i += 1000000)
    {
        time = 0;
        
        for (int z = 0; z < 5; z++)
        {

            binom_heap heap = {};
            heap.child = NULL;
            binom_heap **idx_arr = (binom_heap **) calloc (i, sizeof (*idx_arr));
            
            unsigned *arr = test_arr_generate (i);
            
            time -= clock ();
            for (size_t k = 0; k <= i; k++)
            {
                insert (&heap, arr[k], k, idx_arr);
            }
            time += clock ();
            destroy_heap (&heap, idx_arr, i);
            free (idx_arr);
            free (arr);
        }
            
            
        res_time = time;
        res_time /= 5;

        printf ("%llu %lf\n", i, res_time / CLOCKS_PER_SEC);        
    }
    return 0;
}

unsigned *test_arr_generate (size_t size)
{
    srand (42);

    unsigned *test_arr = (unsigned *) calloc (size, sizeof (int));
    for (size_t i = 0; i < size; i++)
    {
        test_arr [i] = rand ();
    }
    return test_arr;
}
