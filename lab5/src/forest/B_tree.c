#include "B_tree.h"

void B_free_node (B_node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->children_arr != NULL)
    {
        for (unsigned i = 0; i <= node->count; i++)
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

void B_free_tree (void *tree_v)
{
    B_tree_t *tree = tree_v;
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

void *B_init ()
{
    return B_tree_init (64);
}

B_tree_t *B_tree_init (unsigned degree)
{
    B_tree_t *tree = (B_tree_t *) malloc (1 * sizeof (B_tree_t));
    if (!tree) return NULL;
    tree->degree = degree;
    tree->root = B_node_init (degree);
    if (!tree->root) return NULL;
    return tree;
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

int B_add (void *tree_v, unsigned key)
{
    B_tree_t *tree = tree_v;
    if (!tree) return 0;

    if (tree->root == NULL) 
    {
        tree->root = B_node_init (tree->degree);
        if (!tree->root) return -1;
        tree->root->key_arr [0] = key;
        tree->root->count = 1;
        return 0;
    }


    B_node_t *node = tree->root;
    B_node_t *parent = NULL;
    unsigned degree = tree->degree;
    unsigned left = 0;
    unsigned cur_key = 0;
    unsigned mid_idx = (degree - 1) / 2;
    B_node_t *second_node = NULL;
    
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
                tree->root = parent;
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
            parent->children_arr [left] = node;
            parent->children_arr [left + 1] = second_node;

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
    node->key_arr = (unsigned *) calloc (degree + 1, sizeof (unsigned));
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

int B_delete (void *tree_v, unsigned key)
{
    B_tree_t *tree = tree_v;
    if (!tree || !tree->root) return -1;

    B_node_t *node = tree->root;
    unsigned degree = tree->degree;
    unsigned min_count = (degree - 1) / 2;
    unsigned left = 0;

    while (node)
    {
        if (node->count == 0 && node == tree->root)
        {
            if (node->children_arr [0])
            {
                B_node_t *old_root = node;
                tree->root = node->children_arr [0];
                node = tree->root;
                free (old_root->key_arr);
                free (old_root->children_arr);
                free (old_root);
            }
            else break; 
        }

        left = B_find_idx (node, key);
        
        if ((left < node->count) && (node->key_arr [left] == key))
        {
            if (node->children_arr == NULL || node->children_arr [0] == NULL)
            {
                memmove (node->key_arr + left, node->key_arr + left + 1, (node->count - left - 1) * sizeof (unsigned));
                node->count--;
                return 0;
            }
            else
            {
                B_node_t *prev_child = node->children_arr [left];
                while (prev_child && prev_child->children_arr && prev_child->children_arr [0])
                    prev_child = prev_child->children_arr [prev_child->count];
                
                unsigned prev_key = prev_child->key_arr [prev_child->count - 1];
                node->key_arr [left] = prev_key;
                key = prev_key;
                node = node->children_arr [left];
                continue;
            }
        }

        if (node->children_arr == NULL || node->children_arr [0] == NULL) break;

        B_node_t *child = node->children_arr [left];

        if (child->count == min_count)
        {
            B_node_t *left_bro = (left > 0) ? node->children_arr [left - 1] : NULL;
            B_node_t *right_bro = (left < node->count) ? node->children_arr [left + 1] : NULL;

            if (left_bro && left_bro->count > min_count)
            {
                memmove (child->key_arr + 1, child->key_arr, child->count * sizeof (unsigned));
                if (child->children_arr [0])
                    memmove (child->children_arr + 1, child->children_arr, (child->count + 1) * sizeof (B_node_t *));
                
                child->key_arr [0] = node->key_arr [left - 1];
                node->key_arr [left - 1] = left_bro->key_arr [left_bro->count - 1];
                if (child->children_arr [0])
                    child->children_arr [0] = left_bro->children_arr [left_bro->count];
                
                child->count++;
                left_bro->count--;
            }
            else if (right_bro && right_bro->count > min_count)
            {
                child->key_arr [child->count] = node->key_arr [left];
                node->key_arr [left] = right_bro->key_arr [0];
                if (child->children_arr [0])
                    child->children_arr [child->count + 1] = right_bro->children_arr [0];
                
                memmove (right_bro->key_arr, right_bro->key_arr + 1, (right_bro->count - 1) * sizeof (unsigned));
                if (right_bro->children_arr [0])
                    memmove (right_bro->children_arr, right_bro->children_arr + 1, right_bro->count * sizeof (B_node_t *));
                
                child->count++;
                right_bro->count--;
            }
            else 
            {
                if (left_bro)
                {
                    unsigned m_idx = left - 1;
                    left_bro->key_arr [left_bro->count] = node->key_arr [m_idx];
                    memcpy (left_bro->key_arr + left_bro->count + 1, child->key_arr, child->count * sizeof (unsigned));
                    if (child->children_arr [0])
                        memcpy (left_bro->children_arr + left_bro->count + 1, child->children_arr, (child->count + 1) * sizeof (B_node_t *));
                    
                    left_bro->count += child->count + 1;
                    memmove (node->key_arr + m_idx, node->key_arr + m_idx + 1, (node->count - m_idx - 1) * sizeof (unsigned));
                    memmove (node->children_arr + m_idx + 1, node->children_arr + m_idx + 2, (node->count - m_idx - 1) * sizeof (B_node_t *));
                    node->count--;

                    free (child->key_arr);
                    free (child->children_arr);
                    free (child);
                    child = left_bro;
                }
                else 
                {
                    unsigned m_idx = left;
                    child->key_arr [child->count] = node->key_arr [m_idx];
                    memcpy (child->key_arr + child->count + 1, right_bro->key_arr, right_bro->count * sizeof (unsigned));
                    if (right_bro->children_arr [0])
                        memcpy (child->children_arr + child->count + 1, right_bro->children_arr, (right_bro->count + 1) * sizeof (B_node_t *));
                    
                    child->count += right_bro->count + 1;
                    memmove (node->key_arr + m_idx, node->key_arr + m_idx + 1, (node->count - m_idx - 1) * sizeof (unsigned));
                    memmove (node->children_arr + m_idx + 1, node->children_arr + m_idx + 2, (node->count - m_idx - 1) * sizeof (B_node_t *));
                    node->count--;

                    free (right_bro->key_arr);
                    free (right_bro->children_arr);
                    free (right_bro);
                }

                if (node == tree->root && node->count == 0)
                {
                    B_node_t *tmp = node;
                    tree->root = child;
                    node = child;
                    free (tmp->key_arr);
                    free (tmp->children_arr);
                    free (tmp);
                    continue;
                }
            }
        }
        node = child;
    }
    return 0;
}
