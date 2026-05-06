#include "SKIP_list.h"

SKIP_node_t *SKIP_ctr_node (unsigned key, SKIP_node_t *down, SKIP_node_t *next)
{
    SKIP_node_t *node = (SKIP_node_t *) malloc (1 * sizeof (SKIP_node_t));
    if (!node) return NULL;
    node->down = down;
    node->next = next;
    node->key = key;
    return node;
}

SKIP_node_t *SKIP_search (SKIP_node_t *top, unsigned key)
{
    if (!top) return NULL;
    SKIP_node_t *node = top;

    while (node->next && (node->next->key < key))
    {
        node = node->next;
    }
    if (node->down) return SKIP_search (node->down, key);
    
    if (node->key < key && node->next) return node->next;
    return node;
}

int SKIP_add (SKIP_list_t *list, int key)
{
    if (!list) return 1;

    unsigned rand_height = SKIP_get_rand_height ();
    while (list->max_height < rand_height)
    {
        SKIP_re_max_height (list);
    }

    if (list->height < rand_height)
    {
        SKIP_re_height (list, rand_height);
    }

    SKIP_node_t **insert_arr = (SKIP_node_t **) malloc (rand_height * sizeof (SKIP_node_t *));
    if (!insert_arr) return 1;

    unsigned list_idx = rand_height - 1;
    
    SKIP_node_t *node = list->lists_arr [list_idx];
    assert (node->next);
    
    while (1)
    {
        while (node->next && (node->next->key < key))
        {
            node = node->next;
        }

        insert_arr [list_idx] = node;

        assert (list_idx < rand_height);
        if (node->down == NULL) break;

        list_idx--;
        node = node->down;
    }

    SKIP_node_t *down = NULL;
    for (unsigned i = 0; i < rand_height; i++)
    {
        node = SKIP_ctr_node (key, down, insert_arr [i]->next);
        if (!node) 
        {
            free (insert_arr);
            return -1;
        }
        
        down = node;
        if (SKIP_insert_node (insert_arr [i], node))
        {
            free (insert_arr);
            free (node);
            return -1;
        }
    }

    free (insert_arr);
    return 0;
}

int SKIP_insert_node (SKIP_node_t *after_that, SKIP_node_t *this)
{
    if (!after_that) return 1;
    if (!this) return 1;

    SKIP_node_t *swap = after_that->next;
    after_that->next = this;
    this->next = swap;
    return 0;
}

int SKIP_re_height (SKIP_list_t *list, unsigned new_height)
{
    if (!list) return 1;

    for (int hg = ((int) list->height - 1); hg < new_height; hg++)
    {
        list->lists_arr [hg] = SKIP_ctr_list ();
        if (list->lists_arr == NULL) 
        {
            list->height = hg + 1;
            return -1;
        }
    }
    list->height = new_height;
    return 0;
}

SKIP_node_t **SKIP_ctr_list ()
{
    SKIP_node_t **node = (SKIP_node_t **) calloc (2, sizeof (SKIP_node_t*));
    if (!node) return NULL;

    node [0] = (SKIP_node_t *) malloc (sizeof (SKIP_node_t));
    if (!node [0]) return NULL;    
    node [1] = (SKIP_node_t *) malloc (sizeof (SKIP_node_t));
    if (!node [1]) return NULL;

    node [0]->key = INT_MIN;
    node [0]->next = node [1];
    node [1]->key = INT_MAX;
    return node;
}

int SKIP_re_max_height (SKIP_list_t *list)
{
    if (!list) return 1;
    list->max_height *= 2;
    SKIP_node_t **new_lists_arr = (SKIP_node_t **) realloc (list->lists_arr, list->max_height * sizeof (*(list->lists_arr)));
    if (!new_lists_arr)
    {
        list->max_height /= 2;
        return 2;
    }
    list->lists_arr = new_lists_arr;
    return 0;
}

unsigned SKIP_get_rand_height ()
{
    unsigned height = 1;
    while (rand () % 2)
    {
        height++;
    }
    return height;
}

int SKIP_delete (SKIP_list_t *list, unsigned key)
{
    if (!list) return 0;
    SKIP_node_t *node = list->lists_arr [list->height - 1];
    assert (node);
    SKIP_node_t *prev = NULL;
    SKIP_node_t *next = NULL;
    while (node != NULL && node->key != key)
    {   
        while (node->next && (node->next->key < key))
        {
            node = node->next;
        }
        if (node->next && node->next->key == key ) 
        {
            prev = node;
            node = node->next;
            break;
        }
        node = node->down;
    }
    if (node->key == key)
    {
        while (prev)
        {
            next = node->next;
            prev->next = next;
            free (node);

            prev = prev->down;
            if (prev != NULL)
            {
                node = prev->next;
                while (node->next && (node->next->key < key))
                {
                    prev = node;
                    node = node->next;
                }
                assert (node->key == key);
            }
        } 
    }
    return 0;
}

