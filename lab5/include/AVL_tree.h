#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "side.h"

typedef struct AVL_nd
{
    unsigned key;
    int AVL_height;
    struct AVL_nd *right_node;
    struct AVL_nd *left_node;
    struct AVL_nd *parent;
} AVL_node_t;

typedef struct AVL_Tree_t
{
    AVL_node_t *root;
    unsigned count;
} AVL_tree_t;

void       *AVL_init              ();
void        AVL_destructor        (void *tree_v);
void        AVL_change_AVL_height (AVL_node_t *tree);
int         AVL_height            (AVL_node_t *node);
AVL_node_t *AVL_find_min          (AVL_node_t *node);
void        AVL_destroy_node      (AVL_node_t *tree);
AVL_node_t *AVL_rotate            (AVL_node_t *node, side_t side);
AVL_node_t *AVL_insert            (AVL_node_t *tree, unsigned key);
AVL_node_t *AVL_remove            (AVL_node_t *tree, unsigned key);
AVL_node_t *AVL_search            (AVL_tree_t *tree, unsigned key);
int         AVL_add               (void *tree_v, unsigned key);
int         AVL_delete            (void *tree_v, unsigned key);
int         AVL_next              (AVL_node_t *node, unsigned key);


#endif