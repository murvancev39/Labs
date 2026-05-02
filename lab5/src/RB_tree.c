#include "RB_tree.h"

RB_node_t *RB_insert (RB_node_t *tree, RB_node_t *parent, unsigned key)
{
    if (!tree) 
    {
        RB_node_t *node = (RB_node_t *) calloc (1, sizeof (RB_node_t));
        node->key = key;
        node->color = red;
        node->parent = parent;
        return node;
    }

    if (tree->key == key) 
    {
        return tree;
    }

    if (tree->key > key) 
    {
        tree->left_node = RB_insert (tree->left_node, tree, key);
    } 
    else 
    {
        tree->right_node = RB_insert (tree->right_node, tree, key);
    }

    return tree;
}

RB_node_t *RB_add (RB_node_t *tree, unsigned key)
{
    tree = RB_insert (tree, NULL, key);

    RB_node_t *search_node = RB_search (tree, key);

    tree = RB_fix (tree, search_node);

    tree->color == black;

    
}

RB_node_t *RB_fix (RB_node_t *tree, RB_node_t *node)
{
    if (!tree) return;
    if (!node) return;
    RB_node_t *dod = node->parent;
    RB_node_t *pradod = NULL;
    RB_node_t *right_dod = NULL;
    RB_node_t *left_dod = NULL;

    if (!dod)
    {
        node->color = black;
        return tree;
    }

    if (dod->parent)
    {
        pradod = dod->parent;
        left_dod = pradod->left_node;
        right_dod = pradod->right_node;
    }


    if (pradod)
    {
        if (right_dod != NULL && left_dod != NULL)
        {
            if (right_dod->color == red && left_dod->color == red)
            {
                right_dod->color = black;
                left_dod->color = black;
                pradod->color = red;
                return RB_fix (tree, pradod);
            }
        }
        
        if (right_dod == dod)
        {
            if (node == dod->right_node)
            {
                dod->color = black;
                pradod->color = red;
                RB_rotate (pradod, left);
                return;
            }
            RB_rotate (dod, left);
            dod->color = black;
            pradod->color = red;
            RB_rotate (pradod, right);
            return;
        }
        else
        {
            if (node == dod->left_node)
            {
                dod->color = black;
                pradod->color = red;
                RB_rotate (pradod, right);
                return;
            }
            RB_rotate (dod, right);
            dod->color = black;
            pradod->color = red;
            RB_rotate (pradod, left);
            return;
        }
    }
}

RB_node_t *RB_rotate (RB_node_t *node, enum Side side)
{
    if (side == right)
    {
        RB_node_t *A = node;
        RB_node_t *B = A->left_node;
        RB_node_t *C = B->right_node;
        B->right_node = A;
        A->parent = B;
        A->left_node = C;
        if (C) C->parent = A;
        return B;
    }
    RB_node_t *A = node;
    RB_node_t *B = A->right_node;
    RB_node_t *C = B->left_node;
    B->left_node = A;
    A->right_node = C;
    
    A->parent = B;
    if (C) C->parent = A;
    return B;
}

RB_node_t *RB_search (RB_node_t *tree, unsigned key)
{
    RB_node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == key) 
        {
            return node;
        }

        if (node->key > key)
        {
            node = node->left_node;
        }
        else 
        {
            node = node->right_node;
        }
    }
    return NULL;
}
