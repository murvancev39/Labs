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

void clear_tree (CRT_node_t *node)
{
    if (!node) return;
    clear_tree (node->left);
    clear_tree (node->right);
    free (node);
}

void split (CRT_node_t **root, CRT_node_t *node, unsigned key,  CRT_node_t **L, CRT_node_t **R)
{
    if (!node || !root) 
    {
        (*L) = NULL, (*R) = NULL;
        return;
    }
    CRT_node_t *next_node = NULL;
    if (node->key > key)
    {
        (*R) = node;
        next_node = node->left;
        split (root, next_node, key, L, &((*R)->left));
        if ((*R)->left) (*R)->left->dad = (*R); 
        update_size (*R);
    }
    else 
    {
        (*L) = node;
        next_node = node->right;
        split (root, next_node, key, &((*L)->right), R);
        if ((*L)->right) (*L)->right->dad = (*L);
        update_size (*L); 
    }
    return;
}

void update_size (CRT_node_t *node)
{
    if (!node) return;
    int left_sz = node->left ? node->left->size : 0;
    int right_sz = node->right ? node->right->size : 0;
    node->size = 1 + left_sz + right_sz;
    return;
}

CRT_node_t *merge (CRT_node_t *T1, CRT_node_t *T2)
{
    if (!T1) return T2;
    if (!T2) return T1;

    if (T1->priora <= T2->priora)
    {
        T1->right = merge (T1->right, T2);
        if (T1->right) T1->right->dad = T1;
        update_size (T1);
        return T1;
    }
    else
    {
        T2->left = merge (T1, T2->left);
        if (T2->left) T2->left->dad = T2;
        update_size (T2);
        return T2;
    }
    return NULL;
}

void insert (CRT_node_t **root, unsigned key)
{
    if (search(root, key)) return;

    CRT_node_t *T1 = NULL;
    CRT_node_t *T2 = NULL;
    
    split (root, *root, key, &T1, &T2);

    CRT_node_t *T_mid = (CRT_node_t *) calloc (1, sizeof (CRT_node_t));
    T_mid->key = key;
    T_mid->size = 1;
    T_mid->priora = rand () + (rand () << 16);

    *root = merge (merge (T1, T_mid), T2);
    if (*root) (*root)->dad = NULL;
}

void delete (CRT_node_t **root, unsigned key)
{
    if (!search(root, key)) return;

    CRT_node_t *T1 = NULL;
    CRT_node_t *T_mid = NULL;
    CRT_node_t *T2 = NULL;

    split (root, *root, key, &T1, &T2);
    if (T1) T1->dad = NULL;
    if (T2) T2->dad = NULL;
    split (root, T1, key - 1, &T1, &T_mid);
    if (T_mid) 
    {
        free (T_mid);
    }

    *root = merge (T1, T2);
    if (*root) (*root)->dad = NULL;
}

CRT_node_t *max_node (CRT_node_t *node)
{
    if (node == NULL) return NULL;
    if (node->right == NULL)
    {
        return node;
    }
    return max_node (node->right);
}

int search (CRT_node_t **root, unsigned key)
{
    CRT_node_t *node = *root;
    while (node != NULL)
    {
        if (node->key == key) return 1;
        if (node->key > key) node = node->left;
        else node = node->right;
    }
    return 0;    
}

long next (CRT_node_t **root, unsigned key)
{
    long best_key = 0;
    CRT_node_t *node = *root;
    while (node != NULL)
    {
        if (node->key > key)
        {
            best_key = (long) node->key;
            node = node->left;
        }
        else node = node->right;
    }
    return best_key;    
}

long prev (CRT_node_t **root, unsigned key)
{
    long best_key = -1;
    CRT_node_t *node = *root;
    while (node != NULL)
    {
        if (node->key < key)
        {
            best_key = (long) node->key;
            node = node->right;
        }
        else node = node->left;
    }
    return best_key;    
}

long kth (CRT_node_t **root, unsigned k)
{
    CRT_node_t *node = *root;

    while (node != NULL)
    {
        unsigned left_size = get_size (node->left);

        if (left_size  == k)
        {
            return node->key;
        }

        if (k < left_size)
        {
            node = node->left;
        }
        else
        {
            k = k - left_size - 1;
            node = node->right;
        }
    }
    return -1;
}

unsigned get_size (CRT_node_t *root)
{
    if (!root) return 0;
    return root->size;
}
