#ifndef HASH_TABLE_OPEN_H
#define HASH_TABLE_OPEN_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    empty = 0,
    deleted = 0xFFFFFFFF,
} status;

#define EMPTY ((void *) 0)
#define DELETED ((void *) 1)

struct Open_Hash_Table
{
    void **arr;
    size_t size;
    size_t count;
    float load_factor;
    unsigned (*hash_f1) (struct Open_Hash_Table *, void *);
    unsigned (*hash_f2) (struct Open_Hash_Table *, void *);
    unsigned (*idx_f)   (struct Open_Hash_Table *, unsigned cur_num, unsigned cur_step);
};

typedef struct Open_Hash_Table open_hash_table_t;

typedef unsigned (*hash_f_t) (open_hash_table_t *, void *);
typedef unsigned (*idx_f_t)   (open_hash_table_t *, unsigned cur_num, unsigned cur_step);

open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor);
void open_hash_table_dtr (open_hash_table_t *table);
unsigned hash (void *key);
unsigned hash_2 (void *key);
void open_hash_table_rehash (open_hash_table_t *table);


#endif