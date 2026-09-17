#include <stdio.h>
#include <stdlib.h>

unsigned *rand_unsigned_arr (unsigned size)
{
    unsigned *rand_arr = (unsigned *) malloc (size * sizeof (unsigned));
    if (!rand_arr) return NULL;

    for (unsigned i = 0; i < size; i++)
    {
        rand_arr [i] = rand ();
    }
    return rand_arr;
}

unsigned *sorted_unsigned_arr (unsigned size)
{
        unsigned *sorted_arr = (unsigned *) malloc (size * sizeof (unsigned));
    if (!sorted_arr) return NULL;

    for (unsigned i = 0; i < size; i++)
    {
        sorted_arr [i] = size - i;
    }
    return sorted_arr;
}