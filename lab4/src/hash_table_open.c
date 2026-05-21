#include "hash_table_open.h"
#include <math.h>

open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor, hash_f_t hash_f1, unsigned koef_for_f1,
                                        hash_f_t hash_f2, unsigned koef_for_f2, idx_f_t idx_f , cmp_t cmp)
{
    if (size == 0 || !idx_f || !cmp) return NULL;

    open_hash_table_t *table = (open_hash_table_t *) calloc (1, sizeof (open_hash_table_t));
    if (!table) return NULL;

    table->arr = (void **) calloc (size, sizeof (void *));
    if (!table->arr)
    {
        free (table);
        return NULL;
    }

    table->hash_f1 = hash_f1;
    table->koef_for_f1 = koef_for_f1;
    table->hash_f2 = hash_f2;
    table->koef_for_f2 = koef_for_f2;
    table->idx_f = idx_f;
    table->cmp = cmp;
    table->count = 0;
    table->size = size;
    table->max_iterations = (unsigned) log2 ((float) table->size);
    table->load_factor = load_factor;
    return table;
}

void open_hash_table_dtr (open_hash_table_t *table)
{
    if (!table) return;
    free (table->arr);
    free (table);
}

unsigned hash (void *key)
{
    return (*((unsigned *)  key) * 2654435761u);
}

unsigned hash_2 (void *key)
{
    return (*((unsigned *)  key) * 0x9e3779b1u) | 1;
}

int open_hash_table_rehash (open_hash_table_t *table, int add_f (open_hash_table_t *, void *))
{
    if (!table || !add_f || !table->arr) return ERR;

    size_t old_size = table->size;
    void **old_arr = table->arr;

    size_t new_size = old_size * 2;
    void **new_arr = (void **) calloc (new_size, sizeof (void *));
    if (!new_arr) return ALLOC_ERR;

    table->size = new_size;
    table->max_iterations = (unsigned) log2 ((float) table->size);
    table->arr = new_arr;
    table->count = 0;

    for (size_t i = 0; i < old_size; i++)
    {
        if (old_arr [i] != EMPTY && (old_arr [i] != DELETED)) 
        {
            add_f (table, old_arr [i]);
        }
    }

    free(old_arr);
    return OK;
}

// ------------------------------------------------------------------------------------------
// LINEAR / OPEN
// ------------------------------------------------------------------------------------------
int open_hash_table_add (open_hash_table_t *table, void *key)
{
    if (!table || !key || !table->idx_f || !table->arr) return ERR;
    
    if ((float) (table->count + 1) / (float) table->size > table->load_factor) 
    {
        if (open_hash_table_rehash (table, open_hash_table_add) == ALLOC_ERR)
        {
            return ALLOC_ERR;
        }
    }
    
    size_t curr_idx = 0;

    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, (unsigned) i) % table->size;
        if (table->arr [curr_idx] == EMPTY || table->arr [curr_idx] == DELETED)
        {
            table->arr [curr_idx] = key;
            table->count++;
            return OK;
        }

        if (table->cmp && !table->cmp (table->arr [curr_idx], key)) return OK;
    }
    return ERR;
}

long open_hash_table_search (open_hash_table_t *table, void *key)
{
    if (!table || !key || !table->idx_f || !table->arr) return -1;

    size_t curr_idx = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, (unsigned) i) % table->size;
        
        if (table->arr [curr_idx] != EMPTY && table->arr [curr_idx] != DELETED)
        {
            if (table->cmp && !table->cmp (table->arr [curr_idx], key)) return (long) curr_idx;
        }

        if (table->arr [curr_idx] == EMPTY) return -1;
    }
    return -1;
}

int open_hash_table_delete (open_hash_table_t *table, void *key)
{  
    if (!table || !key || !table->idx_f || !table->arr) return ERR;

    size_t curr_idx = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, (unsigned) i) % table->size;

        if (table->arr [curr_idx] != EMPTY && table->arr [curr_idx] != DELETED)
        {
            if (table->cmp && !table->cmp (table->arr [curr_idx], key))
            {
                table->count--;
                table->arr [curr_idx] = DELETED;
                return OK;
            }
        }

        if (table->arr [curr_idx] == EMPTY) return ERR;
    }
    return ERR;
}