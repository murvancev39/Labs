#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct SKIP_Node_t
{
    struct SKIP_Node_t *next;
    struct SKIP_Node_t *down;
    unsigned key;
} SKIP_node_t;

typedef struct SKIP_List_t
{
    unsigned height;
    unsigned max_height;
    SKIP_node_t **lists_arr;
} SKIP_list_t;

SKIP_node_t *SKIP_ctr_node (unsigned key, SKIP_node_t *down, SKIP_node_t *next);
SKIP_node_t *SKIP_search (SKIP_node_t *top, unsigned key);
int SKIP_add (SKIP_list_t *list, int key);
int SKIP_insert_node (SKIP_node_t *after_that, SKIP_node_t *this);
int SKIP_re_height (SKIP_list_t *list, unsigned new_height);
SKIP_node_t **SKIP_ctr_list ();
int SKIP_re_max_height (SKIP_list_t *list);
unsigned SKIP_get_rand_height ();
int SKIP_delete (SKIP_list_t *list, unsigned key);

#endif