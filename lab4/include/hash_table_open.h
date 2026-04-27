#ifndef HASH_TABLE_OPEN_H
#define HASH_TABLE_OPEN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    empty = 0,
    deleted = 0xFFFFFFFF,
} status;

#define EMPTY ((void *) 0)
#define DELETED ((void *) 1)


typedef int (*cmp_t) (void *, void *);
typedef unsigned (*hash_f_t) (unsigned, void *);

struct Open_Hash_Table
{
    void **arr;
    size_t size;
    size_t count;
    float load_factor;
    cmp_t cmp;
    hash_f_t hash_f1;
    unsigned koef_for_f1;
    hash_f_t hash_f2;
    unsigned koef_for_f2;
    unsigned (*idx_f) (struct Open_Hash_Table *, void *, unsigned);
    unsigned max_iterations;
};

typedef struct Open_Hash_Table open_hash_table_t;
typedef unsigned (*idx_f_t)   (open_hash_table_t *, void *, unsigned);



open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor);
void open_hash_table_dtr (open_hash_table_t *table);
unsigned hash (void *key);
unsigned hash_2 (void *key);
void open_hash_table_rehash (open_hash_table_t *table, int add_f (open_hash_table_t *, void *));


#endif