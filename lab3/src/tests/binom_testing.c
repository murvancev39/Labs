#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binom_heap.h"

void **test_arr_generate (size_t size);
int cmp (void *key_1, void *key_2);

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
            heap.cmp = cmp;
            heap.child = NULL;
            binom_heap **idx_arr = (binom_heap **) calloc (i, sizeof (*idx_arr));
            
            void **arr = test_arr_generate (i);
            unsigned *test_arr = arr [0];
            
            time -= clock ();
            for (size_t k = 0; k < i; k++)
            {
                insert (&heap, arr [k], k, idx_arr);
            }
            time += clock ();
            destroy_heap (&heap, idx_arr, i);
            free (idx_arr);
            free (test_arr);
            free (arr);
        }
            
            
        res_time = time;
        res_time /= 5;

        printf ("%lu %lf\n", i, res_time / CLOCKS_PER_SEC);        
    }
    return 0;
}

void **test_arr_generate (size_t size)
{
    srand (42);
    void **arr = malloc (size * sizeof (void *));
    if (!arr) return NULL;

    unsigned *test_arr = (unsigned *) malloc (size * sizeof (int));
    if (!test_arr)
    {
        free (arr);
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        test_arr [i] = rand ();
        arr [i] = test_arr + i;
    }
    return arr;
}



int cmp (void *key_1, void *key_2)
{
    if (*(unsigned *) key_1 > *(unsigned *) key_2) return 1;
    if (*(unsigned *) key_1 < *(unsigned *) key_2) return -1;
    return 0;
}