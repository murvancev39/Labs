#ifndef CRT_TREE_H
#define CRT_TREE_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO ЭТА ВЕРСИЯ РАБОТАЕТ НОРМАЛЬНО ЕСЛИ ЧИСЛА НЕ ПОВТОРЯЮТСЯ
// TODO ПЕРЕДЕЛАТЬ НА UINT

typedef struct CRT_Node
{
    unsigned key;
    int priora;
    unsigned size;
    struct CRT_Node *left;
    struct CRT_Node *right;
    struct CRT_Node *dad;
} CRT_node_t;

void split (CRT_node_t **root, CRT_node_t *node, unsigned key,  CRT_node_t **L, CRT_node_t **R);
void update_size (CRT_node_t *node);
CRT_node_t *merge (CRT_node_t *T1, CRT_node_t *T2);
void insert (CRT_node_t **root, unsigned key);
void delete (CRT_node_t **root, unsigned key);
CRT_node_t *max_node (CRT_node_t *node);
int search (CRT_node_t **root, unsigned key);
long next (CRT_node_t **root, unsigned key);
long prev (CRT_node_t **root, unsigned key);
long kth (CRT_node_t **root, unsigned k);
unsigned get_size (CRT_node_t *root);
void clear_tree (CRT_node_t *node);


#endif