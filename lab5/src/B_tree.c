#include <stdio.h>
#include <stdlib.h>

typedef struct B_Node_t
{
    int leaf;
    int count;
    unsigned *key;
    struct B_Node_t *children;
} B_node_t;

typedef struct B_Tree_t
{
    int degree;
    B_node_t *root;
} B_tree_t;

B_node_t *B_search (B_tree_t *tree)
{
    if (!tree) return;
    B_node_t *node = tree->root;
    while (node)
    {
        for (int i = 0; i < node->n)
    }
    
}

void B_add (B_tree_t *tree, unsigned key)
{
    if (!tree) return;
    
    i
}