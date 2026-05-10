#include "SPL_tree.h"

void SPL_rotate (SPL_tree_t *tree, SPL_node_t *node)
{
    if (!node) return;
    if (!node->dad) return;
    SPL_node_t *dod = node->dad;
    SPL_node_t *pradod = dod->dad;

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
        tree->root = node;
    }
    return;
}

void splay (SPL_tree_t *tree, SPL_node_t *node)
{
    if (!tree) return;
    if (!(tree->root)) return;
    if (!node) return;
    if (!node->dad) return;
    SPL_node_t *cur_node = node;
    SPL_node_t *dod = cur_node->dad;
    SPL_node_t *pradod = NULL;

    while (dod)
    {
        dod = cur_node->dad;
        if (!dod) return;
        pradod = dod->dad;
        if (!pradod)
        {
            SPL_rotate (tree, cur_node);
        }
        else
        {
            if ((dod == pradod->left && cur_node == dod->right) || (dod == pradod->right && cur_node == dod->left))
            {
                SPL_rotate (tree, cur_node);
                SPL_rotate (tree, cur_node);
            }
            else
            {
                SPL_rotate (tree, dod);
                SPL_rotate (tree, cur_node);
            }
        }
    }
    
}

int SPL_search (SPL_tree_t *tree, unsigned key)
{
    if (!tree) return 0;
    SPL_node_t *node = tree->root;
    SPL_node_t *prev = node;

    while (node)
    {
        if (node->key == key) 
        {
            splay (tree, node);
            return 0;
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
    splay (tree, prev);
    return 0;
}

int SPL_add (void *tree_v, unsigned key)
{
    SPL_tree_t *tree = tree_v;
    if (!tree) return 1;
    SPL_node_t *node = tree->root;
    SPL_node_t *prev = node;
    SPL_side which_SPL_side = Root;

    while (node)
    {
        if (node->key == key) 
        {
            splay (tree, node);
            return 0;
        }

        if (node->key > key)
        {
            prev = node;
            node = node->left;
            which_SPL_side = Left;
        }
        else
        {
            prev = node;
            node = node->right;
            which_SPL_side = Right;
        }
    }
    
    SPL_node_t *new_node = (SPL_node_t *) calloc (1, sizeof (SPL_node_t));
    if (!new_node) return 1;
    tree->count++;

    new_node->key = key;
    if (which_SPL_side == Root)
    {
        tree->root = new_node;
        return 0;
    }
    if (which_SPL_side == Left)
    {
        new_node->dad = prev;
        prev->left = new_node;
    }
    else
    {
        new_node->dad = prev;
        prev->right = new_node;
    }
    splay (tree, new_node);
    return 0;
}

int SPL_delete (void *tree_v, unsigned key)
{
    SPL_tree_t *tree = tree_v;
    if (!tree || !tree->root) return 1;

    SPL_search (tree, key);

    if (tree->root->key != key) return 0;

    SPL_node_t *old_root = tree->root;
    SPL_node_t *L = old_root->left;
    SPL_node_t *R = old_root->right;

    free (old_root);
    tree->count--;

    if (!L)
    {
        tree->root = R;
        if (R) R->dad = NULL;
    }
    else
    {
        L->dad = NULL;
        tree->root = L;
        
        SPL_node_t *max_L = SPL_max_node (L);

        splay (tree, max_L); 
        
        tree->root->right = R;
        if (R) R->dad = tree->root;
    }

    return 0;
}

SPL_node_t *SPL_max_node (SPL_node_t *node)
{
    if (!node) return NULL;
    while (node->right)
    {
        node = node->right;
    }
    return node;
}

void *SPL_ctr_tree ()
{
    SPL_tree_t *tree = (SPL_tree_t *) calloc (1, sizeof (SPL_tree_t));
    if (!tree) return NULL;

    tree->root = NULL;
    tree->count = 0;

    return tree;
}

void SPL_destroy_nodes (SPL_node_t *node)
{
    if (!node) return;

    SPL_destroy_nodes (node->left);
    SPL_destroy_nodes (node->right);

    free (node);
}

void SPL_destructor (void *tree_v)
{
    SPL_tree_t *tree = tree_v;
    if (!tree) return;

    if (tree->root) 
    {
        SPL_destroy_nodes (tree->root);
    }

    free (tree);
}