#include "AVL_tree.h"

void *AVL_init ()
{
    AVL_tree_t *tree = (AVL_tree_t *) calloc (1, sizeof (AVL_tree_t));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->count = 0;
    return tree;
}

int AVL_next (AVL_node_t *tree, unsigned key)
{
    int AVL_next = -1;
    AVL_node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == key) return key;
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

int AVL_add (void *tree_v, unsigned key)
{
    AVL_tree_t *tree = tree_v;
    if (!tree) return 1;

    if (AVL_search (tree, key)) return 0;

    tree->root = AVL_insert (tree->root, key);
    if (tree->root) tree->root->parent = NULL;
    
    tree->count++;
    return 0;
}

AVL_node_t *AVL_insert (AVL_node_t *tree, unsigned key)
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
        tree->left_node = AVL_insert (tree->left_node, key);
        tree->left_node->parent = tree;
    }
else
    {
        tree->right_node = AVL_insert (tree->right_node, key);
        tree->right_node->parent = tree;
    }

    AVL_change_AVL_height (tree);

    int balance = AVL_height (tree->left_node) - AVL_height (tree->right_node);
    if (!(balance >= -1 && balance <= 1))
    {
        AVL_node_t *A = tree;
        AVL_node_t *B = NULL;
        if (balance == 2)
        {
            B = tree->left_node;
            if (AVL_height (B->left_node) - AVL_height (B->right_node) >= 0)
            {
                return AVL_rotate (tree, left);
            }
            else
            {
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
                B = AVL_rotate (B, left);
                tree->right_node = B;
                return AVL_rotate (A, right);
            }
        }
    }
    return tree;
}

AVL_node_t *AVL_rotate (AVL_node_t *node, side_t side)
{
    if (side == left)
    {
        AVL_node_t *A = node;
        AVL_node_t *B = A->left_node;
        AVL_node_t *C = B->right_node;

        B->parent = A->parent;
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

    B->parent = A->parent;
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

AVL_node_t *AVL_find_min (AVL_node_t *node)
{
    while (node->left_node) node = node->left_node;
    return node;
}

int AVL_delete (void *tree_v, unsigned key)
{
    AVL_tree_t *tree = tree_v;
    if (!tree || !tree->root) return 1;

    if (AVL_search (tree, key) == NULL) return 0;

    tree->root = AVL_remove (tree->root, key);
    if (tree->root) tree->root->parent = NULL;
    
    tree->count--;
    return 0;
}

AVL_node_t *AVL_remove (AVL_node_t *tree, unsigned key)
{
    if (!tree) return NULL;

    if (key < tree->key)
    {
        tree->left_node = AVL_remove (tree->left_node, key);
        if (tree->left_node) tree->left_node->parent = tree;
    }
    else if (key > tree->key)
    {
        tree->right_node = AVL_remove (tree->right_node, key);
        if (tree->right_node) tree->right_node->parent = tree;
    }
    else
    {
        AVL_node_t *L = tree->left_node;
        AVL_node_t *R = tree->right_node;
        AVL_node_t *P = tree->parent;

        if (!L || !R)
        {
            AVL_node_t *temp = L ? L : R;
            free (tree);
            if (temp) temp->parent = P;
            return temp;
        }
        else
        {
            AVL_node_t *min = AVL_find_min (R);
            tree->key = min->key;
            tree->right_node = AVL_remove (R, min->key);
            if (tree->right_node) tree->right_node->parent = tree;
        }
    }

    AVL_change_AVL_height (tree);

    int balance = AVL_height (tree->left_node) - AVL_height (tree->right_node);

    if (balance > 1)
    {
        if (AVL_height (tree->left_node->left_node) >= AVL_height (tree->left_node->right_node))
        {
            return AVL_rotate (tree, left);
        }
        else
        {
            tree->left_node = AVL_rotate (tree->left_node, right);
            return AVL_rotate (tree, left);
        }
    }
    if (balance < -1)
    {
        if (AVL_height (tree->right_node->right_node) >= AVL_height (tree->right_node->left_node))
        {
            return AVL_rotate (tree, right);
        }
        else
        {
            tree->right_node = AVL_rotate (tree->right_node, left);
            return AVL_rotate (tree, right);
        }
    }

    return tree;
}

AVL_node_t *AVL_search (AVL_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return NULL;

    AVL_node_t *node = tree->root;

    while (node != NULL)
    {
        if (node->key == key)
        {
            return node;
        }

        if (key < node->key)
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

void AVL_destroy_node (AVL_node_t *tree)
{
    if (!tree) return;

    if (tree->left_node)  AVL_destroy_node (tree->left_node);
    if (tree->right_node) AVL_destroy_node (tree->right_node);

    free (tree);
}

void AVL_destructor (void *tree_v)
{
    AVL_tree_t *tree = tree_v;
    if (!tree) return;

    AVL_destroy_node (tree->root);

    free (tree);
}