#include "b_tree.h"

void b_free_node (b_node_t *node)
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
                b_free_node (node->children_arr [i]);
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

void b_free_tree (void *tree_v)
{
    b_tree_t *tree = tree_v;
    if (tree == NULL)
    {
        return;
    }

    if (tree->root != NULL)
    {
        b_free_node (tree->root);
    }

    free (tree);
}

void *b_init ()
{
    return b_tree_init (MIN_TREE_SIZE);
}

b_tree_t *b_tree_init (unsigned degree)
{
    b_tree_t *tree = (b_tree_t *) malloc (1 * sizeof (b_tree_t));
    if (!tree) return NULL;
    tree->degree = degree;
    tree->root = b_node_init (degree);
    if (!tree->root)
    {
        free (tree);
        return NULL;
    }
    return tree;
}

b_node_t *b_search (b_tree_t *tree, unsigned key)
{
    if (!tree) return NULL;
    b_node_t *node = tree->root;
    unsigned *arr = NULL;
    unsigned left = 0, right = 0, mid = 0;
    while (node)
    {
        arr = node->key_arr;
        if (!arr) return NULL;
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

int b_add (void *tree_v, unsigned key)
{
    b_tree_t *tree = tree_v;
    if (!tree) return ERROR;

    if (tree->root == NULL) 
    {
        tree->root = b_node_init (tree->degree);
        if (!tree->root) return ERROR;
        if (!tree->root->key_arr) return ERROR;
        tree->root->key_arr [0] = key;
        tree->root->count = 1;
        return OK;
    }


    b_node_t *node = tree->root;
    b_node_t *parent = NULL;
    unsigned degree = tree->degree;
    unsigned left = 0;
    unsigned cur_key = 0;
    unsigned mid_idx = (degree - 1) / 2;
    b_node_t *second_node = NULL;
    
    while (1)
    {
        if (!node) return ERROR;
        if (node->count == degree)
        {
            left = b_find_idx (node, key);
            if (!node->key_arr) return ERROR;
            if (left < node->count && node->key_arr [left] == key) return OK;
            
            if (parent == NULL)
            {
                parent = b_node_init (tree->degree);
                if (!parent) return ERROR;
                if (!parent->children_arr) return ERROR;
                parent->children_arr [0] = node;
                tree->root = parent;
            }

            if (!node->key_arr) return ERROR;
            cur_key = node->key_arr [mid_idx];

            left = b_find_idx (parent, cur_key);
            
            second_node = b_node_init (degree);
            if (!second_node) return ERROR;

            second_node->count = degree - 1 - mid_idx;

            if (!second_node->key_arr || !node->key_arr) return ERROR;
            memmove (second_node->key_arr, node->key_arr + mid_idx + 1, second_node->count * sizeof (*(node->key_arr)));

            if (node->children_arr && node->children_arr [0] != NULL)
            {
                if (!second_node->children_arr) return ERROR;
                memmove (second_node->children_arr, node->children_arr + mid_idx + 1, (second_node->count + 1) * sizeof (*(node->children_arr)));
            }

            node->count = mid_idx;

            if (!parent->key_arr || !parent->children_arr) return ERROR;
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
        
        left = b_find_idx (node, key);
        if (!node->key_arr) return ERROR;
        if (left < node->count && node->key_arr [left] == key) return OK;

        if (node->children_arr == NULL || node->children_arr [0] == NULL)
        {
            memmove (node->key_arr + 1 + left, node->key_arr + left, (node->count - left) * sizeof (*(node->key_arr)));
            node->key_arr [left] = key;
            node->count++;
            return OK;
        }
        parent = node;
        node = node->children_arr [left];
    }
    return ERROR;
}

b_node_t *b_node_init (unsigned degree)
{
    if (degree < 2) return NULL;
    b_node_t *node = (b_node_t *) calloc (1, sizeof (b_node_t));
    if (!node) return NULL;
    node->key_arr = (unsigned *) calloc (degree + 1, sizeof (unsigned));
    if (!node->key_arr)
    {
        free (node);
        return NULL;
    }
    node->children_arr = (b_node_t **) calloc (degree + 1, sizeof (b_node_t *));
    if (!node->children_arr)
    {
        free (node->key_arr);
        free (node);
        return NULL;
    }
    node->count = 0;
    return node;
}

unsigned b_find_idx (b_node_t *node, unsigned key)
{
    if (!node || !node->key_arr) return 0;
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

int b_delete (void *tree_v, unsigned key)
{
    b_tree_t *tree = tree_v;
    if (!tree || !tree->root) return ERROR;

    b_node_t *node = tree->root;
    unsigned degree = tree->degree;
    unsigned min_count = (degree - 1) / 2;
    unsigned left = 0;

    while (node)
    {
        if (node->count == 0 && node == tree->root)
        {
            if (node->children_arr && node->children_arr [0])
            {
                b_node_t *old_root = node;
                tree->root = node->children_arr [0];
                node = tree->root;
                free (old_root->key_arr);
                free (old_root->children_arr);
                free (old_root);
            }
            else break; 
        }

        left = b_find_idx (node, key);
        
        if (!node->key_arr) return ERROR;
        if ((left < node->count) && (node->key_arr [left] == key))
        {
            if (node->children_arr == NULL || node->children_arr [0] == NULL)
            {
                memmove (node->key_arr + left, node->key_arr + left + 1, (node->count - left - 1) * sizeof (unsigned));
                node->count--;
                return OK;
            }
            else
            {
                b_node_t *prev_child = node->children_arr [left];
                
                while (prev_child && prev_child->children_arr && prev_child->children_arr [0])
                    prev_child = prev_child->children_arr [prev_child->count];
                
                if (!prev_child || !prev_child->key_arr) return ERROR;

                unsigned prev_key = prev_child->key_arr [prev_child->count - 1];
                node->key_arr [left] = prev_key;
                key = prev_key;
                node = node->children_arr [left];
                continue;
            }
        }

        if (node->children_arr == NULL || node->children_arr [0] == NULL) break;

        b_node_t *child = node->children_arr [left];
        if (!child) return ERROR;

        if (child->count == min_count)
        {
            b_node_t *left_bro = (left > 0) ? node->children_arr [left - 1] : NULL;
            b_node_t *right_bro = (left < node->count) ? node->children_arr [left + 1] : NULL;

            if (left_bro && left_bro->count > min_count)
            {
                if (!child->key_arr || !child->children_arr || !left_bro->key_arr || !left_bro->children_arr) return ERROR;
                memmove (child->key_arr + 1, child->key_arr, child->count * sizeof (unsigned));
                if (child->children_arr [0])
                    memmove (child->children_arr + 1, child->children_arr, (child->count + 1) * sizeof (b_node_t *));
                
                child->key_arr [0] = node->key_arr [left - 1];
                node->key_arr [left - 1] = left_bro->key_arr [left_bro->count - 1];
                if (child->children_arr [0])
                    child->children_arr [0] = left_bro->children_arr [left_bro->count];
                
                child->count++;
                left_bro->count--;
            }
            else if (right_bro && right_bro->count > min_count)
            {
                if (!child->key_arr || !child->children_arr || !right_bro->key_arr || !right_bro->children_arr) return ERROR;
                child->key_arr [child->count] = node->key_arr [left];
                node->key_arr [left] = right_bro->key_arr [0];
                if (child->children_arr [0])
                    child->children_arr [child->count + 1] = right_bro->children_arr [0];
                
                memmove (right_bro->key_arr, right_bro->key_arr + 1, (right_bro->count - 1) * sizeof (unsigned));
                if (right_bro->children_arr [0])
                    memmove (right_bro->children_arr, right_bro->children_arr + 1, right_bro->count * sizeof (b_node_t *));
                
                child->count++;
                right_bro->count--;
            }
            else 
            {
                if (left_bro)
                {
                    unsigned m_idx = left - 1;
                    if (!left_bro->key_arr || !left_bro->children_arr || !child->key_arr || !child->children_arr) return ERROR;
                    left_bro->key_arr [left_bro->count] = node->key_arr [m_idx];
                    memcpy (left_bro->key_arr + left_bro->count + 1, child->key_arr, child->count * sizeof (unsigned));
                    if (child->children_arr [0])
                        memcpy (left_bro->children_arr + left_bro->count + 1, child->children_arr, (child->count + 1) * sizeof (b_node_t *));
                    
                    left_bro->count += child->count + 1;
                    memmove (node->key_arr + m_idx, node->key_arr + m_idx + 1, (node->count - m_idx - 1) * sizeof (unsigned));
                    memmove (node->children_arr + m_idx + 1, node->children_arr + m_idx + 2, (node->count - m_idx - 1) * sizeof (b_node_t *));
                    node->count--;

                    free (child->key_arr);
                    free (child->children_arr);
                    free (child);
                    child = left_bro;
                }
                else 
                {
                    unsigned m_idx = left;
                    if (!child->key_arr || !child->children_arr || !right_bro->key_arr || !right_bro->children_arr) return ERROR;
                    child->key_arr [child->count] = node->key_arr [m_idx];
                    memcpy (child->key_arr + child->count + 1, right_bro->key_arr, right_bro->count * sizeof (unsigned));
                    if (right_bro->children_arr [0])
                        memcpy (child->children_arr + child->count + 1, right_bro->children_arr, (right_bro->count + 1) * sizeof (b_node_t *));
                    
                    child->count += right_bro->count + 1;
                    memmove (node->key_arr + m_idx, node->key_arr + m_idx + 1, (node->count - m_idx - 1) * sizeof (unsigned));
                    memmove (node->children_arr + m_idx + 1, node->children_arr + m_idx + 2, (node->count - m_idx - 1) * sizeof (b_node_t *));
                    node->count--;

                    free (right_bro->key_arr);
                    free (right_bro->children_arr);
                    free (right_bro);
                }

                if (node == tree->root && node->count == 0)
                {
                    b_node_t *tmp = node;
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
    return OK;
}