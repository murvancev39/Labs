#ifndef BINOM_HEAP_H
#define BINOM_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Binom_Heap
{
    void *key;
    int degree;
    struct Binom_Heap *parent;
    struct Binom_Heap *child;
    struct Binom_Heap *bro;
    int ins_idx;
    int (*cmp) (void *, void *);
};

typedef struct Binom_Heap binom_heap;

void destroy_heap (binom_heap *heap, binom_heap **idx_arr, int n);
void destroy_node (binom_heap *node);
void *get_min (binom_heap *heap);
binom_heap* merge_lists (binom_heap *l1, binom_heap *l2);
void insert (binom_heap *heap, void *val, int idx, binom_heap **idx_arr);
void merge(binom_heap *heap);
void link_tree (binom_heap *from, binom_heap *where);
int extract_min(binom_heap *heap);
binom_heap* reverse_list (binom_heap *root);
void sift_up (binom_heap *node, binom_heap **idx_arr);
void delete_node (binom_heap *node, binom_heap *heap, binom_heap **idx_arr);
void update_key (binom_heap *node, void *new_val, binom_heap **idx_arr, binom_heap *heap);
void forced_sift_up (binom_heap *node, binom_heap **idx_arr);
#endif