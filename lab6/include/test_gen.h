#ifndef TEST_GEN_H
#define TEST_GEN_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Pair_t
{
    unsigned left;
    unsigned right;
} pair_t;

pair_t *test_pairs_gen (unsigned count, unsigned max_val);
unsigned *test_sequence_gen (unsigned count, unsigned max_val);

#endif