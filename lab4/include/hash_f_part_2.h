#ifndef HASH_F_PART_2
#define HASH_F_PART_2

#include <stdio.h>
#include <stdlib.h>

typedef union
{
    float f;
    unsigned u;
} float_u;

unsigned hash_f_f_int (float key);
unsigned hash_f_f_union (float key);
unsigned hash_f_f_mantiss (float key);
unsigned hash_f_f_exp (float key);
unsigned hash_f_f_mant_exp (float key);

#endif