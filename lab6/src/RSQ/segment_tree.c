#include "segment_tree.h"

void *seg_tree_init (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    seg_tree_t *tree = (seg_tree_t *) malloc (1 * sizeof (seg_tree_t));
    if (!tree) return NULL;

    unsigned min_pow = 1;
    while (min_pow < len)
    {
        min_pow <<= 1;
    }
    tree->min_pow = min_pow;
    

    tree->n = len;
    tree->tree = (long long *) calloc ( min_pow * 2, sizeof (long long));
    if (!tree->tree)
    {
        free (tree);
        return NULL;
    }

    long long *tree_arr = tree->tree;

    for (unsigned i = 0; i < len; i++)
    {
        tree_arr [min_pow + i] = arr [i];
    }

    for (unsigned i = min_pow - 1; i > 0; i--)
    {
        tree_arr [i] = tree_arr [2 * i] + tree_arr [2 * i + 1];
    }
    return tree;
}

void seg_tree_update (seg_tree_t *tree, unsigned idx, unsigned new_val)
{
    if (!tree || !tree->tree ||idx >= tree->n) return;
    
    unsigned i = tree->min_pow + idx;
    long long delta = (long long) new_val - tree->tree [i];

    while (i > 0)
    {
        tree->tree [i] += delta;
        i >>= 1;
    }
    return;
}


long long seg_tree_query (seg_tree_t *tree, unsigned left, unsigned right)
{
    if (!tree || !tree->tree || left > right || right >= tree->n) return 0;

    long long sum = 0;

    left  += tree->min_pow;
    right += tree->min_pow;

    while (left < right)
    {
        if (left & 1)     sum += tree->tree [left++];
        if (!(right & 1)) sum += tree->tree [right--];

        left  >>= 1;
        right >>= 1;
    }
    if (left == right) sum += tree->tree [left];
    return sum;
}

void seg_tree_destructor (seg_tree_t *tree)
{
    if (!tree) return;
    if (tree->tree) free (tree->tree);
    free (tree);
    return;
}