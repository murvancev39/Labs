#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum clr
{
    red = 0,
    black = 1,
} color_t;

typedef struct RB_nd
{
    unsigned key;
    color_t color;
    struct RB_nd *right_node;
    struct RB_nd *left_node;
    struct RB_nd *parent;
} RB_node_t;

enum Side
{
    left = 1,
    right = -1,
};

RB_node_t *RB_insert (RB_node_t *tree, RB_node_t *parent, unsigned key);
RB_node_t *RB_add (RB_node_t *tree, unsigned key);
RB_node_t *RB_fix (RB_node_t *tree, RB_node_t *node);
RB_node_t *RB_rotate (RB_node_t *node, enum Side side);
RB_node_t *RB_search (RB_node_t *tree, unsigned key);

#endif
