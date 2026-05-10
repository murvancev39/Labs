#ifndef CRT_TREE_H
#define CRT_TREE_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CRT_Node
{
    unsigned key;
    int priora;
    unsigned size;
    struct CRT_Node *left;
    struct CRT_Node *right;
    struct CRT_Node *dad;
} CRT_node_t;

typedef struct CRT_tree_t
{
    CRT_node_t *root;
} CRT_tree_t;

void       *CRT_init         ();
void        CRT_update_size  (CRT_node_t *node);
void        CRT_clear_nodes  (CRT_node_t *node);
void        CRT_destroy_tree (void *tree_v);
CRT_node_t *CRT_merge        (CRT_node_t *T1, CRT_node_t *T2);
int         CRT_search       (CRT_tree_t *tree, unsigned key);
int         CRT_add          (void *tree_v, unsigned key);
int         CRT_delete       (void *tree_v, unsigned key);
void        CRT_split        (CRT_node_t *node, unsigned key, CRT_node_t **L, CRT_node_t **R);

#endif