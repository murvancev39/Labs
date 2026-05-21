#ifndef HASH_F_PART_1
#define HASH_F_PART_1

#include <stdio.h>
#include <stdlib.h>
#include "err_def.h"

unsigned hash_f_u_rem (void *key);
unsigned hash_f_u_bits (void *key);
unsigned hash_f_u_knuth (void *key);
int unsigned_cmp (void *key1, void *key2);

#endif