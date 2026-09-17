#ifndef BST_TREE_H
#define BST_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "status_def.h"

typedef struct bst_nd
{
    unsigned key;
    struct bst_nd *right_node;
    struct bst_nd *left_node;
    struct bst_nd *parent;
} bst_node_t;

typedef struct bst_Tree_t
{
    bst_node_t *root;
    unsigned count;
} bst_tree_t;


void       *bst_init         ();
void        bst_destructor   (void *tree_v);
int         bst_add          (void *tree_v, unsigned key);
int         bst_delete       (void *tree_v, unsigned key);
bst_node_t *bst_find         (bst_tree_t *tree, unsigned key);
void        bst_replace_node (bst_node_t **tree, bst_node_t *first, bst_node_t *second);
#endif