#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct seg_tree_t
{
    unsigned n;
    unsigned min_pow;
    long long *tree;
} seg_tree_t;

void     *seg_tree_init       (unsigned *arr, unsigned len);
void      seg_tree_update     (seg_tree_t *tree, unsigned idx, unsigned new_val);
long long seg_tree_query      (seg_tree_t *tree, unsigned left, unsigned right);
void      seg_tree_destructor (seg_tree_t *tree);

#endif