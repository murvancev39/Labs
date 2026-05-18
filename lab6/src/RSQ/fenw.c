#include "fenw.h"

void *fenwik_init (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    fenw_tree_t *tree = (fenw_tree_t *) malloc ( sizeof (fenw_tree_t));
    if (!tree) return NULL;

    tree->n = len;
    tree->tree = (long long *) malloc (sizeof (long long) * (len));
    if (!tree->tree)
    {
        free (tree);
        return NULL;
    }
    long long *tree_arr = tree->tree;

    for (unsigned i = 0; i < len; i++) tree_arr [i] = arr [i];

    for (unsigned i = 0; i <= len; i++)
    {
        unsigned parent = i | (i + 1);
        if (parent <= len) tree_arr [parent] += tree_arr [i];
    }
    
    return tree;
}

long long fenw_prefix_sum (fenw_tree_t *tree, unsigned idx)
{
    long long sum = 0;

    int i  = (int) idx;
    while (i >= 0)
    {
        sum += tree->tree [i];
        i = (i & (i + 1)) - 1;
    }
    return sum;
}

long long fenw_query (fenw_tree_t *tree, unsigned left, unsigned right)
{
    if (!tree || left > right || right >= tree->n) return 0;

    if (left == 0) return fenw_prefix_sum (tree, right);

    return fenw_prefix_sum (tree, right) - fenw_prefix_sum (tree, left - 1);
}

void fenw_update (fenw_tree_t *tree, unsigned idx, unsigned new_val)
{
    if (!tree || idx >= tree->n) return;

    unsigned i = idx;
    long long delta = (long long) new_val - fenw_query (tree, idx, idx);
    
    while (i <= tree->n)
    {
        tree->tree [i] += delta;
        i = i | (i + 1);
    }
    return;
}

void fenw_destructor (fenw_tree_t *tree)
{
    if (!tree) return;
    if (tree->tree) free (tree->tree);
    free (tree);
    return; 
}