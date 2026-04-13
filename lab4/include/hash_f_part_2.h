#ifndef HASH_F_PART_2
#define HASH_F_PART_2

#include <stdio.h>
#include <stdlib.h>

typedef union
{
    float f;
    unsigned u;
} float_u;

unsigned hash_f_f_int (void *key);
unsigned hash_f_f_union (void *key);
unsigned hash_f_f_mantiss (void *key);
unsigned hash_f_f_exp (void *key);
unsigned hash_f_f_mant_exp (void *key);
int float_cmp (void *key1, void *key2);

#endif