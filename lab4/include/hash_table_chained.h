#ifndef HASH_TABLE_CHAINED_H
#define HASH_TABLE_CHAINED_H

#include <stdio.h>
#include <stdlib.h>
#include "err_def.h"

typedef enum
{
    yea = 1,
    no = 0,
} use_load_factor;

typedef struct Node
{
    void *key;
    struct Node *next;
} node_t;

typedef struct Hash_Table
{
    node_t **nodes_arr;
    size_t size;
    unsigned *collision_arr;
    size_t count;
    float load_factor;
    unsigned (*hash_f) (void *);
    int (*cmp) (void *, void *);
} chained_hash_table_t;


chained_hash_table_t *chained_hash_table_ctr (size_t size, float load_factor,
                                unsigned (*hash_f) (void *), int (*cmp) (void *, void *));
void chained_hash_table_clean (chained_hash_table_t *table);
void chained_hash_table_dtr (chained_hash_table_t *table);
void nodes_dtr (node_t *node);
int chained_hash_table_add (chained_hash_table_t *table, void *key);
int rehash (chained_hash_table_t *table, int (*add_func) (chained_hash_table_t *, void *));
int chained_hash_table_delete (chained_hash_table_t *table, void *key);
int chained_hash_table_search (chained_hash_table_t *table, void *key);

#endif