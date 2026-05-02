#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVL_nd
{
    unsigned key;
    int AVL_height;
    struct AVL_nd *right_node;
    struct AVL_nd *left_node;
    struct AVL_nd *parent;
} AVL_node_t;

enum Side
{
    left = 1,
    right = -1,
};

int AVL_next (AVL_node_t *tree, unsigned key);
AVL_node_t *AVL_add (AVL_node_t *tree, unsigned key);
AVL_node_t *AVL_rotate (AVL_node_t *node, enum Side side);
void AVL_change_AVL_height (AVL_node_t *tree);
int AVL_height (AVL_node_t *node);

#endif