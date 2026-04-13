#include "hash_f_part_2.h"

unsigned hash_f_f_int (void *key)
{
    return ((unsigned) *((float *) key));
}

unsigned hash_f_f_union (void *key)
{
    float_u un_key = {.f = *((float *) key)};
    return (un_key.u >> 3);
}

unsigned hash_f_f_mantiss (void *key)
{
    float_u un_key = {.f = *((float *) key)};
    return (un_key.u & 0x7FFFFF);
}

unsigned hash_f_f_exp (void *key)
{
    float_u un_key = {.f = *((float *) key)};
    return ((un_key.u >> 23) & 0xFF);
}

unsigned hash_f_f_mant_exp (void *key)
{
    float_u un_key = {.f = *((float *) key)};
    return ((un_key.u & 0x7FFFFF) * ((un_key.u >> 23) & 0xFF));
}

int float_cmp (void *key1, void *key2)
{
    float f1 = *(float *) key1;
    float f2 = *(float *) key2;

    if (f1 < f2) return -1;
    if (f1 > f2) return 1;
    return 0;
}