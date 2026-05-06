#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct B_Node_t
{
    int leaf;
    int count;
    unsigned *key_arr;
    struct B_Node_t **children_arr;
} B_node_t;

typedef struct B_Tree_t
{
    unsigned degree;
    B_node_t *root;
} B_tree_t;

void B_free_node (B_node_t *node);
void B_free_tree (B_tree_t *tree);
B_tree_t *B_tree_init (unsigned degree);
B_node_t *B_search (B_tree_t *tree, unsigned key);
int B_add (B_tree_t *tree, unsigned key);
B_node_t *B_node_init (unsigned degree);
unsigned B_find_idx (B_node_t *node, unsigned key);
int B_delete (B_tree_t *tree, unsigned key);

#endif