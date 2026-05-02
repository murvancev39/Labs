#ifndef SPL_TREE_H
#define SPL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SPL_Node
{
    unsigned key;
    struct SPL_Node *left;
    struct SPL_Node *right;
    struct SPL_Node *dad;
} SPL_node_t;

typedef enum Side 
{
    Root = -1,
    Left = 0,
    Right = 1,
} side;

void SPL_rotate (SPL_node_t **root, SPL_node_t *node);
void splay (SPL_node_t **root, SPL_node_t *node);
int SPL_search (SPL_node_t **root, unsigned key);
void SPL_add (SPL_node_t **root, unsigned key);
void SPL_delete (SPL_node_t **root, unsigned key);
SPL_node_t *SPL_max_node (SPL_node_t **root);

#endif
