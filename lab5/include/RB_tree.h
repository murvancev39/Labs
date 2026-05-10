#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "side.h"

typedef enum clr
{
    red = 0,
    black = 1,
} color_t;

typedef struct RB_nd
{
    unsigned key;
    color_t color;
    struct RB_nd *parent;
    struct RB_nd *left_node;
    struct RB_nd *right_node;
} RB_node_t;

typedef struct RB_Tree_t
{
    unsigned count;
    RB_node_t *root;
} RB_tree_t;


void       *RB_init ();
void        RB_destroy_tree  (void *tree_v);
void        RB_destroy_nodes (RB_node_t *node);
int         RB_add           (void *tree_v, unsigned key);
int         RB_delete        (void *tree_v, unsigned key);
RB_node_t  *RB_search_n      (RB_node_t *tree, unsigned key);
RB_node_t  *RB_search        (RB_tree_t *tree, unsigned key);
RB_node_t  *RB_rotate        (RB_node_t *node, side_t side);
void        RB_fix           (RB_tree_t *tree, RB_node_t *node);
RB_node_t * RB_insert        (RB_node_t *tree, RB_node_t *parent, unsigned key);
void        RB_fix_delete    (RB_tree_t *tree, RB_node_t *node, RB_node_t *dod);
void        RB_transplant    (RB_tree_t *tree, RB_node_t *first, RB_node_t *second);

#endif
