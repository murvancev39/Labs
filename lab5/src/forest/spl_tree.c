#include "spl_tree.h"

void spl_rotate (spl_tree_t *tree, spl_node_t *node)
{
    if (!node || !node->dad) return;
    
    spl_node_t *dod = node->dad;
    spl_node_t *pradod = dod->dad;

    if (node == dod->left)
    {
        dod->left = node->right;
        if (dod->left) dod->left->dad = dod;
        node->right = dod;
    }
    else
    {
        dod->right = node->left;
        if (dod->right) dod->right->dad = dod;
        node->left = dod;
    }

    dod->dad = node;
    node->dad = pradod;

    if (pradod)
    {
        if (pradod->right == dod) pradod->right = node;
        else pradod->left = node;
    }
    else
    {
        tree->root = node;
    }
}

void splay (spl_tree_t *tree, spl_node_t *node)
{
    if (!tree || !node) return;

    while (node->dad)
    {
        spl_node_t *dod = node->dad;
        spl_node_t *pradod = dod->dad;

        if (!pradod)
        {
            spl_rotate (tree, node);
        }
        else
        {
            if ((dod == pradod->left && node == dod->right) || 
                (dod == pradod->right && node == dod->left))
            {
                spl_rotate (tree, node);
                spl_rotate (tree, node);
            }
            else
            {
                spl_rotate (tree, dod);
                spl_rotate (tree, node);
            }
        }
    }
}

int spl_search (spl_tree_t *tree, unsigned key)
{
    if (!tree) return ERROR;
    if (!tree->root) return OK;

    spl_node_t *node = tree->root;
    spl_node_t *prev = NULL;

    while (node)
    {
        prev = node;
        if (node->key == key) 
        {
            splay (tree, node);
            return OK;
        }

        if (node->key > key) node = node->left;
        else node = node->right;
    }
    
    if (prev) splay (tree, prev);
    return OK;
}

int spl_add (void *tree_v, unsigned key)
{
    spl_tree_t *tree = tree_v;
    if (!tree) return ERROR;

    if (!tree->root)
    {
        tree->root = (spl_node_t *) calloc (1, sizeof (spl_node_t));
        if (!tree->root) return ERROR;
        tree->root->key = key;
        tree->count++;
        return OK;
    }

    spl_node_t *node = tree->root;
    spl_node_t *prev = NULL;
    spl_side side = Root;

    while (node)
    {
        prev = node;
        if (node->key == key) 
        {
            splay (tree, node);
            return OK;
        }

        if (node->key > key)
        {
            node = node->left;
            side = Left;
        }
        else
        {
            node = node->right;
            side = Right;
        }
    }
    
    spl_node_t *new_node = (spl_node_t *) calloc (1, sizeof (spl_node_t));
    if (!new_node) return ERROR;

    new_node->key = key;
    new_node->dad = prev;
    if (side == Left) prev->left = new_node;
    else prev->right = new_node;

    tree->count++;
    splay (tree, new_node);
    return OK;
}

int spl_delete (void *tree_v, unsigned key)
{
    spl_tree_t *tree = tree_v;
    if (!tree || !tree->root) return ERROR;

    spl_search (tree, key);

    if (tree->root->key != key) return OK;

    spl_node_t *old_root = tree->root;
    spl_node_t *L = old_root->left;
    spl_node_t *R = old_root->right;

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
        spl_node_t *max_L = spl_max_node (L);
        splay (tree, max_L); 
        tree->root->right = R;
        if (R) R->dad = tree->root;
    }

    return OK;
}

spl_node_t *spl_max_node (spl_node_t *node)
{
    if (!node) return NULL;
    while (node->right) node = node->right;
    return node;
}

void *spl_ctr_tree ()
{
    spl_tree_t *tree = (spl_tree_t *) calloc (1, sizeof (spl_tree_t));
    return tree;
}

void spl_destroy_nodes (spl_node_t *node)
{
    if (!node) return;
    spl_destroy_nodes (node->left);
    spl_destroy_nodes (node->right);
    free (node);
}

void spl_destructor (void *tree_v)
{
    spl_tree_t *tree = tree_v;
    if (!tree) return;
    if (tree->root) spl_destroy_nodes (tree->root);
    free (tree);
}