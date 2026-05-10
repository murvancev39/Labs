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
    
    if (node->next && node->next->key == key) 
    {
        return node->next;
    }

    return node; 
}

int SKIP_add (void *list_v, unsigned key)
{
    SKIP_list_t *list = list_v;
    if (!list) return 1;

    unsigned rand_height = SKIP_get_rand_height ();
    
    while (list->max_height < rand_height) SKIP_re_max_height (list);
    if (list->height < rand_height) SKIP_re_height (list, rand_height);

    SKIP_node_t **insert_arr = (SKIP_node_t **) malloc (rand_height * sizeof (SKIP_node_t *));
    if (!insert_arr) return 1;

    int list_idx = (int) list->height - 1;
    SKIP_node_t *node = list->lists_arr [list_idx];

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

    SKIP_node_t *down_ptr = NULL;
    for (unsigned i = 0; i < rand_height; i++)
    {
        SKIP_node_t *new_node = SKIP_ctr_node (key, down_ptr, NULL);
        if (!new_node)
        {
            free (insert_arr);
            return -1;
        }

        SKIP_insert_node (insert_arr [i], new_node);
        
        down_ptr = new_node;
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

SKIP_node_t *SKIP_ctr_list () 
{
    SKIP_node_t *head = (SKIP_node_t *) calloc (1, sizeof (SKIP_node_t));
    SKIP_node_t *tail = (SKIP_node_t *) calloc (1, sizeof (SKIP_node_t));
    
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

int SKIP_re_height (SKIP_list_t *list, unsigned new_height)
{
    if (!list) return 1;

    for (unsigned hg = list->height; hg < new_height; hg++)
    {
        SKIP_node_t *new_head = SKIP_ctr_list ();
        if (!new_head) return -1;

        if (hg > 0) 
        {
            new_head->down = list->lists_arr [hg - 1];
        }

        list->lists_arr [hg] = new_head;
    }
    
    list->height = new_height;
    return 0;
}

int SKIP_re_max_height (SKIP_list_t *list)
{
    if (!list) return 1;

    unsigned old_max = list->max_height;
    list->max_height *= 2;

    SKIP_node_t **new_lists_arr = (SKIP_node_t **) realloc (list->lists_arr, list->max_height * sizeof (SKIP_node_t *));
    
    if (!new_lists_arr)
    {
        list->max_height = old_max;
        return 2;
    }

    for (unsigned i = old_max; i < list->max_height; i++)
    {
        new_lists_arr [i] = NULL;
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

int SKIP_delete (void *list_v, unsigned key)
{
    SKIP_list_t *list = list_v;
    if (!list || list->height == 0) return 1;

    SKIP_node_t *node = list->lists_arr [list->height - 1];

    for (int hg = (int) list->height - 1; hg >= 0; hg--)
    {
        while (node->next && (node->next->key < key))
        {
            node = node->next;
        }

        if (node->next && node->next->key == key)
        {
            SKIP_node_t *target = node->next;
            node->next = target->next;
            free (target);
        }

        if (hg > 0)
        {
            node = node->down;
        }
    }

    return 0;
}

void SKIP_destructor (void *list_v)
{
    SKIP_list_t *list = list_v;
    if (!list) return;

    for (unsigned hg = 0; hg < list->height; hg++)
    {
        SKIP_node_t *current = list->lists_arr [hg];
        while (current)
        {
            SKIP_node_t *next_to_free = current->next;
            free (current);
            current = next_to_free;
        }
    }

    free (list->lists_arr);
    free (list);
    return;
}


void *SKIP_init ()
{
    SKIP_list_t *list = (SKIP_list_t *) calloc (1, sizeof (SKIP_list_t));
    if (!list) return NULL;

    list->max_height = 4;
    list->height = 0;
    
    list->lists_arr = (SKIP_node_t **) calloc (list->max_height, sizeof (SKIP_node_t *));
    if (!list->lists_arr)
    {
        free (list);
        return NULL;
    }

    if (SKIP_re_height (list, 1) != 0)
    {
        free (list->lists_arr);
        free (list);
        return NULL;
    }

    return list;
}