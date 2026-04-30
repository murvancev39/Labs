#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    unsigned key;
    struct Node *left;
    struct Node *right;
    struct Node *dad;
} node_t;

typedef enum Side 
{
    Root = -1,
    Left = 0,
    Right = 1,
} side;

void rotate_splay (node_t **root, node_t *node)
{
    if (!node) return;
    if (!node->dad) return;
    node_t *dod = node->dad;
    node_t *pradod = dod->dad;

    if (node == dod->left)
    {
        dod->left = node->right;
        if (dod->left) dod->left->dad = dod;
        node->right = dod;
        dod->dad = node;
        node->dad = pradod;
    }
    else
    {
        dod->right = node->left;
        if (dod->right) dod->right->dad = dod;
        node->left = dod;
        dod->dad = node;
        node->dad = pradod;
    }

    if (pradod)
    {
        if (pradod->right == dod) pradod->right = node;
        else pradod->left = node;
    }
    else
    {
        *root = node; 
    }
}


void splay (node_t **root, node_t *node)
{
    if (!root) return;
    if (!(*root)) return;
    if (!node) return;
    if (!node->dad) return;
    node_t *cur_node = node;
    node_t *dod = cur_node->dad;
    node_t *pradod = NULL;

    while (dod)
    {
        dod = cur_node->dad;
        if (!dod) return;
        pradod = dod->dad;
        if (!pradod)
        {
            rotate (root, cur_node);
        }
        else
        {
            if ((dod == pradod->left && cur_node == dod->right) || (dod == pradod->right && cur_node == dod->left))
            {
                rotate (root, cur_node);
                rotate (root, cur_node);
            }
            else
            {
                rotate (root, dod);
                rotate (root, cur_node);
            }
        }
    }
    
}

int search_splay (node_t **root, unsigned key)
{
    if (!root) return 0;
    node_t *node = *root;
    node_t *prev = node;

    while (node)
    {
        if (node->key == key) 
        {
            splay (root, node);
            return 1;
        }

        if (node->key > key)
        {
            prev = node;
            node = node->left;
        }
        else
        {
            prev = node;
            node = node->right;
        }
    }
    splay (root, prev);
    return 0;
}

void add_splay (node_t **root, unsigned key)
{
    if (!root) return;
    node_t *node = *root;
    node_t *prev = node;
    side which_side = Root;

    while (node)
    {
        if (node->key == key) 
        {
            splay (root, node);
            return;
        }

        if (node->key > key)
        {
            prev = node;
            node = node->left;
            which_side = Left;
        }
        else
        {
            prev = node;
            node = node->right;
            which_side = Right;
        }
    }
    
    node_t *new_node = (node_t *) calloc (1, sizeof (node_t));
    new_node->key = key;
    if (which_side == Root)
    {
        *root = new_node;
        return;
    }
    if (which_side == Left)
    {
        new_node->dad = prev;
        prev->left = new_node;
    }
    else
    {
        new_node->dad = prev;
        prev->right = new_node;
    }
    splay (root, new_node);
    return;
}

void delete_splay (node_t **root, unsigned key)
{
    if (!root) return;
    if (!(*root)) return;
    if (!search_splay (root, key)) return;
    node_t *R = (*root)->right;
    node_t *L = (*root)->left;
    free (*root);
    if (!L)
    {
        *root = R;
        if (R) R->dad = NULL;
        return;
    }
    node_t *max_node = max_node_splay (&L);
    splay (&L, max_node);
    L->right = R;
    if (R) R->dad = L;
    L->dad = NULL;
    *root = L;
    return;
}

node_t *max_node_splay (node_t **root)
{
    node_t *node = *root;
    node_t *prev = NULL;
    while (node)
    {
        prev = node;
        node = node->right;
    }
    return prev;
}