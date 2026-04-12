#include "hash_f_part_2.h"

unsigned hash_f_f_int (float key)
{
    return ((unsigned) key) % 1000;
}

unsigned hash_f_f_union (float key)
{
    float_u un_key = {.f = key};
    return (un_key.u >> 3) % 1000;
}

unsigned hash_f_f_mantiss (float key)
{
    float_u un_key = {.f = key};
    return (un_key.u & 0x7FFFFF) % 1000;
}

unsigned hash_f_f_exp (float key)
{
    float_u un_key = {.f = key};
    return ((un_key.u >> 23) & 0xFF) % 1000;
}

unsigned hash_f_f_mant_exp (float key)
{
    float_u un_key = {.f = key};
    return ((un_key.u & 0x7FFFFF) * ((un_key.u >> 23) & 0xFF)) % 1000;
}