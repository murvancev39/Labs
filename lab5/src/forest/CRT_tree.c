#include "CRT_tree.h"

void *CRT_init ()
{
    CRT_tree_t *tree = (CRT_tree_t *) calloc (1, sizeof (CRT_tree_t));
    if (!tree) return NULL;
    tree->root = NULL;
    return tree;
}

void CRT_update_size (CRT_node_t *node)
{
    if (!node) return;
    int left_sz = node->left ? node->left->size : 0;
    int right_sz = node->right ? node->right->size : 0;
    node->size = 1 + left_sz + right_sz;
}

void CRT_split (CRT_node_t *node, unsigned key, CRT_node_t **L, CRT_node_t **R)
{
    if (!node) 
    {
        (*L) = NULL; (*R) = NULL;
        return;
    }

    if (node->key > key)
    {
        (*R) = node;
        CRT_split (node->left, key, L, &((*R)->left));
        if ((*R)->left) (*R)->left->dad = (*R); 
        CRT_update_size (*R);
    }
    else 
    {
        (*L) = node;
        CRT_split (node->right, key, &((*L)->right), R);
        if ((*L)->right) (*L)->right->dad = (*L);
        CRT_update_size (*L); 
    }
    if (*L) (*L)->dad = NULL;
    if (*R) (*R)->dad = NULL;
}

CRT_node_t *CRT_merge (CRT_node_t *T1, CRT_node_t *T2)
{
    if (!T1) return T2;
    if (!T2) return T1;

    if (T1->priora <= T2->priora)
    {
        T1->right = CRT_merge (T1->right, T2);
        if (T1->right) T1->right->dad = T1;
        CRT_update_size (T1);
        return T1;
    }
    else
    {
        T2->left = CRT_merge (T1, T2->left);
        if (T2->left) T2->left->dad = T2;
        CRT_update_size (T2);
        return T2;
    }
}

int CRT_search (CRT_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return 0;
    CRT_node_t *node = tree->root;
    while (node != NULL)
    {
        if (node->key == key) return 1;
        if (node->key > key) node = node->left;
        else node = node->right;
    }
    return 0;        
}

int CRT_add (void *tree_v, unsigned key)
{
    CRT_tree_t *tree = tree_v;
    if (!tree) return 1;
    if (CRT_search (tree, key)) return 0; 

    CRT_node_t *T1 = NULL;
    CRT_node_t *T2 = NULL;
    
    CRT_split (tree->root, key, &T1, &T2);

    CRT_node_t *T_mid = (CRT_node_t *) calloc (1, sizeof (CRT_node_t));
    if (!T_mid) return 1; 
    T_mid->key = key;
    T_mid->size = 1;
    T_mid->priora = rand () + 1;

    tree->root = CRT_merge (CRT_merge (T1, T_mid), T2);
    if (tree->root) tree->root->dad = NULL;
    
    return 0;
}

int CRT_delete (void *tree_v, unsigned key)
{
    CRT_tree_t *tree = tree_v;
    if (!tree || !tree->root) return 1;
    if (!CRT_search (tree, key)) return 0; 

    CRT_node_t *T1 = NULL;
    CRT_node_t *T_mid = NULL;
    CRT_node_t *T2 = NULL;

    CRT_split (tree->root, key, &T1, &T2);
    CRT_split (T1, key - 1, &T1, &T_mid);

    if (T_mid) 
    {
        free (T_mid);
    }

    tree->root = CRT_merge (T1, T2);
    if (tree->root) tree->root->dad = NULL;
    
    return 0;
}

void CRT_clear_nodes (CRT_node_t *node)
{
    if (!node) return;
    CRT_clear_nodes (node->left);
    CRT_clear_nodes (node->right);
    free (node);
}

void CRT_destroy_tree (void *tree_v)
{
    CRT_tree_t *tree = tree_v;
    if (!tree) return;
    CRT_clear_nodes (tree->root);
    free (tree);
}