#include "hash_f_part_1.h"

unsigned hash_f_u_rem (unsigned val)
{
    return val % 1000;
}

unsigned hash_f_u_bits (unsigned val)
{
    return (val >> 3) % 1000;
}

unsigned hash_f_u_knuth (unsigned key)
{
    const double A = 0.6180339887;
    double val = (double) key * A;
    return (unsigned int) (1000 * (val - (long) val));
}

