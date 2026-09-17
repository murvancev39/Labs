#include "test_gen.h"

pair_t *test_pairs_gen (unsigned count, unsigned max_val)
{
    if (!count) return NULL;
    
    pair_t *arr = (pair_t *) malloc (count * sizeof (pair_t));
    unsigned swap = 0;
    for (unsigned i = 0; i < count; i++)
    {
        arr [i].left  = (rand () % max_val);
        arr [i].right = (rand () % max_val);
        if (arr [i].left > arr [i].right)
        {
            swap = arr [i].left;
            arr [i].left = arr [i].right;
            arr [i].right = swap;
        }
    }
    return arr;
}

unsigned *test_sequence_gen (unsigned count, unsigned max_val)
{
    if (!count) return NULL;

    unsigned *arr = (unsigned *) malloc (count * sizeof (unsigned));
    if (!arr) return NULL;
    if (max_val == RAND_MAX)
    {
        for (unsigned i = 0; i < count; i++)
        {
            arr [i] = rand ();
        }
    }
    else
    {
        for (unsigned i = 0; i < count; i++)
        {
            arr [i] = rand () % max_val;
        }
    }

    return arr;
}