#ifndef BST_TREE_H
#define BST_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BST_nd
{
    unsigned key;
    struct BST_nd *right_node;
    struct BST_nd *left_node;
    struct BST_nd *parent;
} BST_node_t;

typedef struct BST_Tree_t
{
    BST_node_t *root;
    unsigned count;
} BST_tree_t;


void       *BST_init         ();
void        BST_destructor   (void *tree_v);
int         BST_add          (void *tree_v, unsigned key);
int         BST_delete       (void *tree_v, unsigned key);
BST_node_t *BST_find         (BST_tree_t *tree, unsigned key);
void        BST_replace_node (BST_node_t **tree, BST_node_t *first, BST_node_t *second);
#endif