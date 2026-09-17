#include "skip_list.h"

skip_node_t *skip_ctr_node (unsigned key, skip_node_t *down, skip_node_t *next)
{
    skip_node_t *node = (skip_node_t *) malloc (sizeof (skip_node_t));
    if (!node) return NULL;
    node->down = down;
    node->next = next;
    node->key = key;
    return node;
}

skip_node_t *skip_search (skip_node_t *top, unsigned key)
{
    if (!top) return NULL;
    skip_node_t *node = top;

    while (node->next && (node->next->key < key))
    {
        node = node->next;
    }

    if (node->down) return skip_search (node->down, key);
    
    if (node->next && node->next->key == key) 
    {
        return node->next;
    }

    return node; 
}

int skip_add (void *list_v, unsigned key)
{
    skip_list_t *list = list_v;
    if (!list) return ERROR;

    unsigned rand_height = skip_get_rand_height ();
    
    while (list->max_height < rand_height) 
    {
        if (skip_re_max_height (list) != OK) return ERROR;
    }
    if (list->height < rand_height) 
    {
        if (skip_re_height (list, rand_height) != OK) return ERROR;
    }

    skip_node_t **insert_arr = (skip_node_t **) malloc (rand_height * sizeof (skip_node_t *));
    if (!insert_arr) return ERROR;

    int list_idx = (int) list->height - 1;
    skip_node_t *node = list->lists_arr [list_idx];

    while (list_idx >= 0)
    {
        while (node->next && (node->next->key < key))
        {
            node = node->next;
        }

        if (list_idx < (int) rand_height)
        {
            insert_arr [list_idx] = node;
        }

        if (list_idx > 0)
        {
            node = node->down;
        }
        list_idx--;
    }

    skip_node_t *down_ptr = NULL;
    for (unsigned i = 0; i < rand_height; i++)
    {
        skip_node_t *new_node = skip_ctr_node (key, down_ptr, NULL);
        if (!new_node)
        {
            free (insert_arr);
            return ERROR;
        }

        skip_insert_node (insert_arr [i], new_node);
        
        down_ptr = new_node;
    }

    free (insert_arr);
    return OK;
}

int skip_insert_node (skip_node_t *after_that, skip_node_t *this)
{
    if (!after_that || !this) return ERROR;

    skip_node_t *swap = after_that->next;
    after_that->next = this;
    this->next = swap;
    return OK;
}

skip_node_t *skip_ctr_list () 
{
    skip_node_t *head = (skip_node_t *) calloc (1, sizeof (skip_node_t));
    skip_node_t *tail = (skip_node_t *) calloc (1, sizeof (skip_node_t));
    
    if (!head || !tail) 
    {
        free (head); 
        free (tail);
        return NULL;
    }

    head->key = INT_MIN;
    tail->key = INT_MAX;
    head->next = tail;

    return head;
}

int skip_re_height (skip_list_t *list, unsigned new_height)
{
    if (!list) return ERROR;

    for (unsigned hg = list->height; hg < new_height; hg++)
    {
        skip_node_t *new_head = skip_ctr_list ();
        if (!new_head) return ERROR;

        if (hg > 0) 
        {
            new_head->down = list->lists_arr [hg - 1];
        }

        list->lists_arr [hg] = new_head;
    }
    
    list->height = new_height;
    return OK;
}

int skip_re_max_height (skip_list_t *list)
{
    if (!list) return ERROR;

    unsigned old_max = list->max_height;
    unsigned new_max = list->max_height * 2;

    skip_node_t **new_lists_arr = (skip_node_t **) realloc (list->lists_arr, new_max * sizeof (skip_node_t *));
    
    if (!new_lists_arr)
    {
        return ERROR;
    }

    for (unsigned i = old_max; i < new_max; i++)
    {
        new_lists_arr [i] = NULL;
    }

    list->lists_arr = new_lists_arr;
    list->max_height = new_max;
    return OK;
}

unsigned skip_get_rand_height ()
{
    unsigned height = 1;
    while (rand () % 2)
    {
        height++;
    }
    return height;
}

int skip_delete (void *list_v, unsigned key)
{
    skip_list_t *list = list_v;
    if (!list || list->height == 0) return ERROR;

    skip_node_t *node = list->lists_arr [list->height - 1];

    for (int hg = (int) list->height - 1; hg >= 0; hg--)
    {
        while (node->next && (node->next->key < key))
        {
            node = node->next;
        }

        if (node->next && node->next->key == key)
        {
            skip_node_t *target = node->next;
            node->next = target->next;
            free (target);
        }

        if (hg > 0)
        {
            node = node->down;
        }
    }

    return OK;
}

void skip_destructor (void *list_v)
{
    skip_list_t *list = list_v;
    if (!list) return;

    for (unsigned hg = 0; hg < list->height; hg++)
    {
        skip_node_t *current = list->lists_arr [hg];
        while (current)
        {
            skip_node_t *next_to_free = current->next;
            free (current);
            current = next_to_free;
        }
    }

    free (list->lists_arr);
    free (list);
}

void *skip_init ()
{
    skip_list_t *list = (skip_list_t *) calloc (1, sizeof (skip_list_t));
    if (!list) return NULL;

    list->max_height = 4;
    list->height = 0;
    
    list->lists_arr = (skip_node_t **) calloc (list->max_height, sizeof (skip_node_t *));
    if (!list->lists_arr)
    {
        free (list);
        return NULL;
    }

    if (skip_re_height (list, 1) != OK)
    {
        free (list->lists_arr);
        free (list);
        return NULL;
    }

    return list;
}