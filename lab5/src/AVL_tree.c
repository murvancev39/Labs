#include <stdio.h>
#include <stdlib.h>

typedef struct nd
{
    unsigned key;
    int height;
    struct nd *right_node;
    struct nd *left_node;
    struct nd *parent;
} node_t;

enum Side
{
    left = 1,
    right = -1,
};

int next (node_t *tree, unsigned key);
node_t *add (node_t *tree, unsigned key);
node_t *rotate (node_t *node, enum Side side);
void change_height (node_t *tree);
int height (node_t *node);

int next (node_t *tree, unsigned key)
{
    int next = -1;
    int _key = (int) key;
    node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == _key) return _key;
        if (node->key > key)
        {
            next = node->key;
            node = node->left_node;
        }
        else 
        {
            node = node->right_node;
        }
    }
    return next;
}

node_t *add (node_t *tree, unsigned key)
{
    if (!tree) 
    {
        node_t *node = (node_t *) calloc (1, sizeof (node_t));
        node->key = key;
        node->height = 1;
        return node;
    }
    if (tree->key == key)
    {
        return tree;
    }
    if (tree->key > key)    
    {
        tree->left_node = add (tree->left_node, key);
        tree->left_node->parent = tree;
    }
   else
    {
        tree->right_node = add (tree->right_node, key);
        tree->right_node->parent = tree;
    }

    change_height (tree);

    int balance = height (tree->left_node) - height (tree->right_node);
    if (!(balance >= -1 && balance <= 1))
    {
        node_t *A = tree;
        node_t *B = NULL;
        node_t *C = NULL;
        if (balance == 2)
        {
            B = tree->left_node;
            if (height (B->left_node) - height (B->right_node) >= 0)
            {
                return rotate (tree, left);
            }
            else
            {
                // printf ("\n\nSEGFOLT _ 1\n\n");
                B = rotate (B, right);
                tree->left_node = B;
                return rotate (A, left);
            }
        }
        else
        {
            B = tree->right_node;
            
            if (height (B->left_node) - height (B->right_node) <= 0)
            {
                return rotate (tree, right);
            }
            else
            {
                // printf ("%u %u")
                // printf ("\n\nSEGFOLT %u %u %p %p _ 2\n\n", B->key, tree->key, B->left_node, B->right_node);
                B = rotate (B, left);
                // printf ("\n\nSEGFOLT _ 2\n\n");
                tree->right_node = B;
                return rotate (A, right);
            }
        }
    }
    return tree;
}

node_t *rotate (node_t *node, enum Side side)
{
    if (side == left)
    {
        node_t *A = node;
        node_t *B = A->left_node;
        node_t *C = B->right_node;
        B->right_node = A;
        A->parent = B;
        A->left_node = C;
        if (C) C->parent = A;
        change_height (A);
        change_height (B);
        return B;
    }
    node_t *A = node;
    node_t *B = A->right_node;
    node_t *C = B->left_node;
    B->left_node = A;
    A->right_node = C;
    
    A->parent = B;
    if (C) C->parent = A;
    
    change_height (A);
    change_height (B);
    return B;
}

void change_height (node_t *tree)
{
    tree->height = height (tree->left_node);
    if (tree->height < height (tree->right_node))
    {
        tree->height = height (tree->right_node);
    }
    tree->height++;
    return;
}

int height (node_t *node)
{
    if (!node) return 0;
    return (int) node->height;
}

