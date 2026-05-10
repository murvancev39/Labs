#ifndef SPL_TREE_H
#define SPL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SPL_Node
{
    unsigned key;
    struct SPL_Node *dad;
    struct SPL_Node *left;
    struct SPL_Node *right;
} SPL_node_t;

typedef struct SPL_Tree_t
{
    unsigned count;
    SPL_node_t *root;
} SPL_tree_t;

typedef enum SPL_Side 
{
    Left = 0,
    Right = 1,
    Root = -1,
} SPL_side;

void       *SPL_ctr_tree      ();
void        SPL_destroy_nodes (SPL_node_t *node);
void        SPL_destructor    (void *tree_v);
SPL_node_t *SPL_max_node      (SPL_node_t *node);
int         SPL_search        (SPL_tree_t *tree, unsigned key);
int         SPL_add           (void *tree_v, unsigned key);
int         SPL_delete        (void *tree_v, unsigned key);
void        splay             (SPL_tree_t *tree, SPL_node_t *node);
void        SPL_rotate        (SPL_tree_t *tree, SPL_node_t *node);
#endif
