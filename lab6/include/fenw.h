#ifndef FENW_H
#define FENW_H

#include <stdio.h>
#include <stdlib.h>

typedef struct fenw_tree_t
{
    unsigned n;
    long long *tree;
} fenw_tree_t;

void      fenw_destructor   (fenw_tree_t *tree);
void     *fenwik_init       (unsigned *arr, unsigned len);
long long fenw_prefix_sum   (fenw_tree_t *tree, unsigned idx);
long long fenw_query        (fenw_tree_t *tree, unsigned left, unsigned right);
void      fenw_update       (fenw_tree_t *tree, unsigned idx, unsigned new_val);

#endif