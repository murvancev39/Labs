#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct B_Node_t
{
    int leaf;
    int count;
    unsigned *key_arr;
    struct B_Node_t **children_arr;
} B_node_t;

typedef struct B_Tree_t
{
    unsigned degree;
    B_node_t *root;
} B_tree_t;

void B_free_node (B_node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->children_arr != NULL)
    {
        for (int i = 0; i <= node->count; i++)
        {
            if (node->children_arr [i] != NULL)
            {
                B_free_node (node->children_arr [i]);
            }
        }
        free (node->children_arr);
    }

    if (node->key_arr != NULL)
    {
        free (node->key_arr);
    }

    free (node);
}

void B_free_tree (B_tree_t *tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->root != NULL)
    {
        B_free_node (tree->root);
    }

    free (tree);
}

B_tree_t *B_tree_init (unsigned degree)
{
    B_tree_t *tree = (B_tree_t *) malloc (1 * sizeof (B_tree_t));
    if (!tree) return NULL;
    tree->degree = degree;
    tree->root = B_node_init (degree);
    if (!tree->root) return NULL;
}

B_node_t *B_search (B_tree_t *tree, unsigned key)
{
    if (!tree) return NULL;
    B_node_t *node = tree->root;
    unsigned *arr = NULL;
    unsigned left = 0, right = 0, mid = 0;
    while (node)
    {
        arr = node->key_arr;
        left = 0, right = node->count, mid = right / 2;
        while (left < right)
        {
            mid = left + (right - left) / 2;
            if (arr [mid] > key)      right = mid;
            else if (arr [mid] < key) left = mid + 1;
            else return node;
        }
        if (node->children_arr && node->children_arr [left]) node = node->children_arr [left];
        else break;
    }
    return NULL;
}

int B_add (B_tree_t *tree, unsigned key)
{
    if (!tree) return 0;
    B_node_t *node = tree->root;
    B_node_t *parent = NULL;
    unsigned degree = tree->degree;
    unsigned left = 0, right = 0, mid = 0;
    unsigned *arr = NULL;
    unsigned cur_key = 0;
    unsigned mid_idx = (degree - 1) / 2;
    B_node_t *second_node = NULL;
    unsigned create_parent_flag = 0;
    
    while (1)
    {
        if (node->count == degree)
        {
            left = B_find_idx (node, key);
            if (left < node->count && node->key_arr [left] == key) return 0;
            
            if (parent == NULL)
            {
                parent = B_node_init (tree->degree);
                if (!parent) return -1;
                parent->children_arr [0] = node;
                parent->count++;
                tree->root = parent;
                create_parent_flag = 1;
            }

            cur_key = node->key_arr [mid_idx];

            left = B_find_idx (parent, cur_key);
            
            second_node = B_node_init (degree);
            if (!second_node) return -1;

            second_node->count = degree - 1 - mid_idx;

            memmove (second_node->key_arr, node->key_arr + mid_idx + 1, second_node->count * sizeof (*(node->key_arr)));

            if (node->children_arr && node->children_arr [0] != NULL)
            {
                memmove (second_node->children_arr, node->children_arr + mid_idx + 1, (second_node->count + 1) * sizeof (*(node->children_arr)));
            }

            node->count = mid_idx;

            memmove (parent->key_arr + left + 1, parent->key_arr + left, (parent->count - left) * sizeof (*(parent->key_arr)));
            memmove (parent->children_arr + left + 1, parent->children_arr + left, (parent->count - left + 1) * sizeof (*(parent->children_arr)));

            parent->key_arr [left] = cur_key;
            parent->children_arr [left] = second_node;

            parent->count++;

            if (cur_key < key)
            {
                node = second_node;
            }
        }
        
        left = B_find_idx (node, key);
        if (left < node->count && node->key_arr [left] == key) return 0;

        if (node->children_arr == NULL || node->children_arr [0] == NULL)
        {
            memmove (node->key_arr + 1 + left, node->key_arr + left, (node->count - left) * sizeof (*(node->key_arr)));
            node->key_arr [left] = key;
            node->count++;
            return 0;
        }
        parent = node;
        node = node->children_arr [left];
    }
    return 1;
}

B_node_t *B_node_init (unsigned degree)
{
    if (degree < 2) return NULL;
    B_node_t *node = (B_node_t *) calloc (1, sizeof (B_node_t));
    if (!node) return NULL;
    node->key_arr = (unsigned) calloc (degree, sizeof (unsigned));
    node->children_arr = (B_node_t **) calloc (degree + 1, sizeof (B_node_t *));
    node->count = 0;
    return node;
}

unsigned B_find_idx (B_node_t *node, unsigned key)
{
    unsigned *arr = node->key_arr;

    unsigned left = 0;
    unsigned right = node->count;
    unsigned mid = right / 2;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (arr [mid] > key)      right = mid;
        else if (arr [mid] < key) left = mid + 1;
        else return mid;
    }
    return left;
}

int B_delete (B_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return -1;

    B_node_t *node = tree->root;
    unsigned degree = tree->degree;
    unsigned min_count = (degree - 1) / 2;
    unsigned left = 0;
    while (node)
    {
        left = B_find_idx (node, key);
        
        if ((left < node->count) && (node->key_arr [left] == key))
        {
            if (node->children_arr == NULL || node->children_arr [0] == NULL)
            {
                memmove (node->key_arr + left, node->key_arr + left + 1, (node->count - left - 1) * sizeof (*(node->key_arr)));
                node->count--;
                return 0;
            }
            else
            {
                B_node_t *prev_child = node->children_arr [left];
                while (prev_child && prev_child->children_arr && prev_child->children_arr [0])
                {
                    prev_child = prev_child->children_arr [prev_child->count];
                }
                unsigned prev_key = prev_child->key_arr [prev_child->count - 1];

                node->key_arr [left] = prev_key;

                key = prev_key;
                node = node->children_arr [left];
                continue;
            }
        }
        // if (node->children_arr != NULL && node->children_arr [0] != NULL) return 0;

        B_node_t *child = node->children_arr [left];

        if (child->count == min_count)
        {
            B_node_t *left_bro = NULL;
            if (left > 0) left_bro = node->children_arr [left - 1];
            B_node_t *right_bro = NULL;
            if (left < node->count) right_bro = node->children_arr [left + 1];

            if (left_bro && left_bro->count > min_count)
            {
                memmove (child->key_arr + 1, child->key_arr, child->count * sizeof (*(child->key_arr)));
                if (child->children_arr != NULL && child->children_arr [0] != NULL)
                {
                    memmove (child->children_arr + 1, child->children_arr, child->count * sizeof(*(child->children_arr)));
                    child->children_arr [0] = left_bro->children_arr [left_bro->count];
                }
                child->key_arr [0] = node->key_arr [left - 1];
                node->key_arr [left - 1] = left_bro->key_arr [left_bro->count - 1];
                child->count++;
                left_bro->count--;
            }
            else
            {
                B_node_t *bro = left_bro;
                if (!bro) bro = right_bro;
                int merge_idx = left - 1;
                if (!bro) merge_idx = left;

                if (left_bro)
                {
                    bro->key_arr [bro->count] = node->key_arr [merge_idx];
                    memmove (bro->key_arr + bro->count + 1, child->key_arr,  child->count * sizeof (*(child->key_arr)));
                    if (child->children_arr != NULL && child->children_arr [0] != NULL)
                    {
                        memmove (bro->children_arr + bro->count + 1, child->children_arr, (child->count + 1) * sizeof (*(child->children_arr)));
                    }
                    bro->count += child->count + 1;

                    memmove (node->key_arr + merge_idx, node->key_arr + merge_idx + 1, (node->count - merge_idx - 1) * sizeof (*(node->key_arr)));
                    memmove (node->children_arr + merge_idx + 1, node->children_arr + merge_idx + 2, (node->count - merge_idx - 1) * sizeof(*(node->children_arr)));
                    node->count--;

                    free (child->key_arr);
                    free (child->children_arr);
                    free (child);
                    child = bro;
                }
                else
                {
                    child->key_arr [child->count] = node->key_arr [merge_idx];
                    memcpy (child->key_arr + child->count + 1, right_bro->key_arr, right_bro->count * sizeof (*(right_bro->key_arr)));
                    if (child->children_arr && child->children_arr [0]) 
                    {
                        memcpy (child->children_arr + child->count + 1, right_bro->children_arr, (right_bro->count + 1) * sizeof (*(right_bro->children_arr)));
                    }
                    child->count += right_bro->count + 1;
                    
                    memmove (node->key_arr + merge_idx, node->key_arr + merge_idx + 1, (node->count - merge_idx - 1) * sizeof(*(node->key_arr)));
                    memmove (node->children_arr + merge_idx + 1, node->children_arr + merge_idx + 2, (node->count - merge_idx - 1) * sizeof(*(node->children_arr)));
                    node->count--;

                    free (right_bro->children_arr);
                    free (right_bro->key_arr);
                    free (right_bro);

                    memmove(node->children_arr + merge_idx + 1, node->children_arr + merge_idx + 2, (node->count - merge_idx) * sizeof(*(node->children_arr)));
                }

                if (node == tree->root && node->count == 0)
                {
                    tree->root = child;
                    free (node->key_arr);
                    free (node->children_arr);
                    free (node);
                }
            }
        }
        node = child;
    }

    return 0;
}

