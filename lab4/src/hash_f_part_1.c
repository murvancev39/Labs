#include "hash_f_part_1.h"

unsigned hash_f_u_rem (void *key)
{
    return *((unsigned *) key) % 1000;
}

unsigned hash_f_u_bits (void *key)
{
    return (*((unsigned *) key) >> 3) % 1000;
}

unsigned hash_f_u_knuth (void *key)
{
    const double A = 0.6180339887;
    double val = ((double) *((unsigned *) key)) * A;
    return (unsigned int) (1000 * (val - (long) val));
}

int unsigned_cmp (void *key1, void *key2)
{
    if (*((unsigned *) key1) > *((unsigned *) key2)) return 1;
    if (*((unsigned *) key1) == *((unsigned *) key2)) return 0;
    return -1;
}

