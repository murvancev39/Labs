#include "crt_tree.h"

void *crt_init ()
{
    crt_tree_t *tree = (crt_tree_t *) calloc (1, sizeof (crt_tree_t));
    if (!tree) return NULL;
    tree->root = NULL;
    return tree;
}

void crt_update_size (crt_node_t *node)
{
    if (!node) return;
    int left_sz = node->left ? node->left->size : 0;
    int right_sz = node->right ? node->right->size : 0;
    node->size = 1 + left_sz + right_sz;
}

static void crt_split_inner (crt_node_t *node, unsigned key, 
                             crt_node_t **first, crt_node_t **second)
{
    if (!node) 
    {
        (*first) = NULL; (*second) = NULL;
        return;
    }

    if (node->key > key)
    {
        *second = node;
        crt_split_inner (node->left, key, first, &((*second)->left));
        if ((*second)->left) (*second)->left->dad = (*second); 
        crt_update_size (*second);
    }
    else 
    {
        *first = node;
        crt_split_inner (node->right, key, &((*first)->right), second);
        if ((*first)->right) (*first)->right->dad = (*first);
        crt_update_size (*first); 
    }
}

void crt_split (crt_node_t *node, unsigned key, crt_node_t **first, crt_node_t **second)
{
    crt_split_inner(node, key, first, second);
    if (*first) (*first)->dad = NULL;
    if (*second) (*second)->dad = NULL;
}

crt_node_t *crt_merge (crt_node_t *T1, crt_node_t *T2)
{
    if (!T1) return T2;
    if (!T2) return T1;

    if (T1->priority <= T2->priority)
    {
        T1->right = crt_merge (T1->right, T2);
        if (T1->right) T1->right->dad = T1;
        crt_update_size (T1);
        return T1;
    }
    else
    {
        T2->left = crt_merge (T1, T2->left);
        if (T2->left) T2->left->dad = T2;
        crt_update_size (T2);
        return T2;
    }
}

int crt_search (crt_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return 0;
    crt_node_t *node = tree->root;
    while (node != NULL)
    {
        if (node->key == key) return 1;
        if (node->key > key) node = node->left;
        else node = node->right;
    }
    return 0;         
}

int crt_add (void *tree_v, unsigned key)
{
    crt_tree_t *tree = tree_v;
    if (!tree) return ERROR;
    if (crt_search (tree, key)) return OK; 

    crt_node_t *T1 = NULL;
    crt_node_t *T2 = NULL;
    
    crt_split (tree->root, key, &T1, &T2);

    crt_node_t *T_mid = (crt_node_t *) calloc (1, sizeof (crt_node_t));
    if (!T_mid) return ERROR; 
    T_mid->key = key;
    T_mid->size = 1;
    T_mid->priority = rand () + 1;

    tree->root = crt_merge (crt_merge (T1, T_mid), T2);
    if (tree->root) tree->root->dad = NULL;
    
    return OK;
}

int crt_delete (void *tree_v, unsigned key)
{
    crt_tree_t *tree = tree_v;
    if (!tree || !tree->root) return ERROR;
    if (!crt_search (tree, key)) return OK; 

    crt_node_t *T1 = NULL;
    crt_node_t *T2 = NULL;

    crt_split (tree->root, key, &T1, &T2);
    
    crt_node_t *curr = T1;
    while (curr->right != NULL) 
    {
        curr = curr->right;
    }
    
    crt_node_t *new_T1 = crt_merge(curr->left, curr->right);
    if (new_T1) new_T1->dad = curr->dad;
    
    if (curr->dad) 
    {
        curr->dad->right = new_T1;
        crt_node_t *walker = curr->dad;
        while (walker) 
        {
            crt_update_size(walker);
            walker = walker->dad;
        }
    } 
    else 
    {
        T1 = new_T1;
    }
    
    free(curr);

    tree->root = crt_merge (T1, T2);
    if (tree->root) tree->root->dad = NULL;
    
    return OK;
}

void crt_clear_nodes (crt_node_t *node)
{
    if (!node) return;
    crt_clear_nodes (node->left);
    crt_clear_nodes (node->right);
    free (node);
}

void crt_destroy_tree (void *tree_v)
{
    crt_tree_t *tree = tree_v;
    if (!tree) return;
    crt_clear_nodes (tree->root);
    free (tree);
}