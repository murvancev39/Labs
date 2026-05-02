#include "AVL_tree.h"

int AVL_next (AVL_node_t *tree, unsigned key)
{
    int AVL_next = -1;
    int _key = (int) key;
    AVL_node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == _key) return _key;
        if (node->key > key)
        {
            AVL_next = node->key;
            node = node->left_node;
        }
        else 
        {
            node = node->right_node;
        }
    }
    return AVL_next;
}

AVL_node_t *AVL_add (AVL_node_t *tree, unsigned key)
{
    if (!tree) 
    {
        AVL_node_t *node = (AVL_node_t *) calloc (1, sizeof (AVL_node_t));
        node->key = key;
        node->AVL_height = 1;
        return node;
    }
    if (tree->key == key)
    {
        return tree;
    }
    if (tree->key > key)    
    {
        tree->left_node = AVL_add (tree->left_node, key);
        tree->left_node->parent = tree;
    }
   else
    {
        tree->right_node = AVL_add (tree->right_node, key);
        tree->right_node->parent = tree;
    }

    AVL_change_AVL_height (tree);

    int balance = AVL_height (tree->left_node) - AVL_height (tree->right_node);
    if (!(balance >= -1 && balance <= 1))
    {
        AVL_node_t *A = tree;
        AVL_node_t *B = NULL;
        AVL_node_t *C = NULL;
        if (balance == 2)
        {
            B = tree->left_node;
            if (AVL_height (B->left_node) - AVL_height (B->right_node) >= 0)
            {
                return AVL_rotate (tree, left);
            }
            else
            {
                // printf ("\n\nSEGFOLT _ 1\n\n");
                B = AVL_rotate (B, right);
                tree->left_node = B;
                return AVL_rotate (A, left);
            }
        }
        else
        {
            B = tree->right_node;
            
            if (AVL_height (B->left_node) - AVL_height (B->right_node) <= 0)
            {
                return AVL_rotate (tree, right);
            }
            else
            {
                // printf ("%u %u")
                // printf ("\n\nSEGFOLT %u %u %p %p _ 2\n\n", B->key, tree->key, B->left_node, B->right_node);
                B = AVL_rotate (B, left);
                // printf ("\n\nSEGFOLT _ 2\n\n");
                tree->right_node = B;
                return AVL_rotate (A, right);
            }
        }
    }
    return tree;
}

AVL_node_t *AVL_rotate (AVL_node_t *node, enum Side side)
{
    if (side == left)
    {
        AVL_node_t *A = node;
        AVL_node_t *B = A->left_node;
        AVL_node_t *C = B->right_node;
        B->right_node = A;
        A->parent = B;
        A->left_node = C;
        if (C) C->parent = A;
        AVL_change_AVL_height (A);
        AVL_change_AVL_height (B);
        return B;
    }
    AVL_node_t *A = node;
    AVL_node_t *B = A->right_node;
    AVL_node_t *C = B->left_node;
    B->left_node = A;
    A->right_node = C;
    
    A->parent = B;
    if (C) C->parent = A;
    
    AVL_change_AVL_height (A);
    AVL_change_AVL_height (B);
    return B;
}

void AVL_change_AVL_height (AVL_node_t *tree)
{
    tree->AVL_height = AVL_height (tree->left_node);
    if (tree->AVL_height < AVL_height (tree->right_node))
    {
        tree->AVL_height = AVL_height (tree->right_node);
    }
    tree->AVL_height++;
    return;
}

int AVL_height (AVL_node_t *node)
{
    if (!node) return 0;
    return (int) node->AVL_height;
}

