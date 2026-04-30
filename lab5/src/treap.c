#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO ЭТА ВЕРСИЯ РАБОТАЕТ НОРМАЛЬНО ЕСЛИ ЧИСЛА НЕ ПОВТОРЯЮТСЯ
// TODO ПЕРЕДЕЛАТЬ НА UINT

typedef struct Node
{
    void *key;
    int priora;
    unsigned size;
    struct Node *left;
    struct Node *right;
    struct Node *dad;
} node_t;

typedef struct hd
{
    node_t *head;
    int (*cmp) (void *, void *);
} root_t;

void split (root_t *root, node_t *node, void *key,  node_t **L, node_t **R);
void update_size (node_t *node);
node_t *merge (node_t *T1, node_t *T2);
void insert (root_t *root, void *key);
void delete (root_t *root, void *key);
node_t *max_node (node_t *node);
int search (root_t *root, void *key);
void *next (root_t *root, void *key);
void *prev (root_t *root, void *key);
void *kth (root_t *root, unsigned k);
unsigned get_size (node_t *root);
int cmp_long (void *a, void *b);
void clear_tree (node_t *node);

int main ()
{
    root_t tree = {NULL, cmp_long};
    char cmd [20];
    long val;

    while (scanf ("%s", cmd) != EOF)
    {
        if (strcmp (cmd, "kth") == 0)
        {
            scanf ("%ld", &val);
            void *res = kth (&tree, (unsigned) val);
            if (res) printf ("%ld\n", *(long *) res);
            else printf ("none\n");
        }
        else if (strcmp (cmd, "insert") == 0)
        {
            scanf ("%ld", &val);
            if (!search (&tree, &val))
            {
                long *p = (long *) malloc (sizeof (long));
                *p = val;
                insert (&tree, p);
            }
        }
        else if (strcmp (cmd, "delete") == 0)
        {
            scanf ("%ld", &val);
            delete (&tree, &val);
        }
        else if (strcmp (cmd, "exists") == 0)
        {
            scanf ("%ld", &val);
            if (search (&tree, &val)) printf ("true\n");
            else printf ("false\n");
        }
        else if (strcmp (cmd, "next") == 0)
        {
            scanf ("%ld", &val);
            void *res = next (&tree, &val);
            if (res) printf ("%ld\n", *(long *) res);
            else printf ("none\n");
        }
        else if (strcmp (cmd, "prev") == 0)
        {
            scanf ("%ld", &val);
            void *res = prev (&tree, &val);
            if (res) printf ("%ld\n", *(long *) res);
            else printf ("none\n");
        }
    }
    
    clear_tree (tree.head);
    return 0;
}

void clear_tree (node_t *node)
{
    if (!node) return;
    clear_tree (node->left);
    clear_tree (node->right);
    free (node->key);
    free (node);
}

void split (root_t *root, node_t *node, void *key,  node_t **L, node_t **R)
{
    if (!node || !root) 
    {
        (*L) = NULL, (*R) = NULL;
        return;
    }
    int ind = root->cmp (node->key, key);
    node_t *next_node = NULL;
    if (ind > 0)
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

void update_size (node_t *node)
{
    if (!node) return;
    int left_sz = node->left ? node->left->size : 0;
    int right_sz = node->right ? node->right->size : 0;
    node->size = 1 + left_sz + right_sz;
    return;
}

node_t *merge (node_t *T1, node_t *T2)
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

void insert (root_t *root, void *key)
{
    node_t *T1 = NULL;
    node_t *T2 = NULL;
    split (root, root->head, key, &T1, &T2);
    if (T1) T1->dad = NULL;    
    if (T2) T2->dad = NULL; 
    
    node_t *node = max_node (T1);

    if (node != NULL && !root->cmp (node->key, key))
    {
        root->head = merge (T1, T2);
        free (key);
        return;
    }
    node_t *T_mid = (node_t *) calloc (1, sizeof (node_t));
    T_mid->key = key;
    T_mid->size = 1;
    T_mid->priora = rand () + (rand () << 16);
    T_mid = merge (T1, T_mid);
    T_mid = merge (T_mid, T2);
    if (T_mid->dad) T_mid->dad = NULL;
    root->head = T_mid;
    return;
}

void delete (root_t *root, void *key)
{
    node_t *T1 = NULL;
    node_t *T2 = NULL;
    node_t *T_mid = NULL;
    split (root, root->head, key, &T1, &T2);
    if (T1) T1->dad = NULL;    
    if (T2) T2->dad = NULL;    
    if (!T1)
    {
        root->head = T2;
        return;
    }

    node_t *node = max_node (T1);
    if (root->cmp (node->key, key))
    {
        root->head = merge (T1, T2);
        return;
    }

    if (node->dad) 
    {
        node_t *parent = node->dad;
        if (node->left) node->left->dad = node->dad;
        parent->right = node->left;

        node_t *cur_node = parent;
        while (cur_node)
        {
            update_size (cur_node);
            cur_node = cur_node->dad;
        }
        free (node->key);
        free (node);
        root->head = merge (T1, T2);
        if (root->head) root->head->dad = NULL;
        return;
    }
    T1 = node->left;
    if (node->left) node->left->dad = NULL;
    root->head = merge (T1, T2);
    free (node->key);
    free (node);
    return;
}

node_t *max_node (node_t *node)
{
    if (node == NULL) return NULL;
    if (node->right == NULL)
    {
        return node;
    }
    return max_node (node->right);
}

int search (root_t *root, void *key)
{
    node_t *node = root->head;
    int ind = 0;
    while (node != NULL)
    {
        ind = root->cmp (node->key, key);
        if (ind == 0) return 1;
        if (ind > 0) node = node->left;
        else node = node->right;
    }
    return 0;    
}

void *next (root_t *root, void *key)
{
    void *best_key = NULL;
    node_t *node = root->head;
    while (node != NULL)
    {
        if (root->cmp (node->key, key) > 0)
        {
            best_key = node->key;
            node = node->left;
        }
        else node = node->right;
    }
    return best_key;    
}

void *prev (root_t *root, void *key)
{
    void *best_key = NULL;
    node_t *node = root->head;
    while (node != NULL)
    {
        if (root->cmp (node->key, key) < 0)
        {
            best_key = node->key;
            node = node->right;
        }
        else node = node->left;
    }
    return best_key;    
}

void *kth (root_t *root, unsigned k)
{
    node_t *node = root->head;

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
    return NULL;
}

unsigned get_size (node_t *root)
{
    if (!root) return 0;
    return root->size;
}

int cmp_long (void *a, void *b)
{
    long val_a = *(long *)a;
    long val_b = *(long *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}
