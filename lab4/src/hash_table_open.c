#include "hash_table_open.h"

open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor, hash_f_t hash_f1, unsigned koef_for_f1,
                                        hash_f_t hash_f2, unsigned koef_for_f2, idx_f_t idx_f , cmp_t cmp)
{
    open_hash_table_t *table = (open_hash_table_t *) calloc (1, sizeof (open_hash_table_t));
    table->arr = (unsigned *) calloc (size, sizeof (unsigned));
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
    free (table->arr);
    free (table);
}

unsigned hash (void *key)
{
    return ((unsigned) key * 2654435761u);
}

unsigned hash_2 (void *key)
{
    return ((unsigned)  key * 0x9e3779b1u) | 1;
}

void open_hash_table_rehash (open_hash_table_t *table, int add_f (open_hash_table_t *, void *))
{
    size_t old_size = table->size;
    void **old_arr = table->arr;

    table->size *= 2;
    table->max_iterations = (unsigned) log2 ((float) table->size);
    table->arr = (void **) calloc (table->size, sizeof (void *));
    
    table->count = 0;

    for (size_t i = 0; i < old_size; i++)
    {
        if (old_arr [i] != EMPTY && (old_arr [i] != DELETED)) add_f (table, old_arr [i]);
    }

    free(old_arr);
}

// ------------------------------------------------------------------------------------------
// LINEAR
// ------------------------------------------------------------------------------------------
int open_hash_table_add (open_hash_table_t *table, void *key)
{
    if (!table) return 1;
    if (!key) return 1;
    if ((float) (table->count + 1) / table->size > table->load_factor) open_hash_table_rehash (table, open_hash_table_add);
    size_t curr_idx = 0;

    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, i) % table->size;
        if (table->arr [curr_idx] == EMPTY || table->arr [curr_idx] == DELETED)
        {
            table->arr [curr_idx] = key;
            table->count++;
            return 0;
        }

        if (!table->cmp (table->arr [curr_idx], key)) return 0;

    }
    return 1;
}

long open_hash_table_search (open_hash_table_t *table, void *key)
{
    if (!table) return 1;
    if (!key) return 1;

    size_t curr_idx = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, i) % table->size;
        if (!table->cmp (table->arr [curr_idx], key)) return (long) curr_idx;

        if (table->arr [curr_idx] == EMPTY) return -1;
    }
    return -1;
}


int open_hash_table_delete (open_hash_table_t *table, void *key)
{  
    if (!table) return 1;
    if (!key) return 1;

    size_t curr_idx = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        curr_idx = table->idx_f (table, key, i) % table->size;

        if (!table->cmp (table->arr [curr_idx], key))
        {
            table->count--;
            table->arr [curr_idx] = DELETED;
            return 0;
        }

        if (table->arr [curr_idx] == EMPTY) return 0;
    }
    return 0;
}

// int open_hash_table_add_cuckoo (open_hash_table_t *table, void *key)
// {
//     if (!table) return 1;
//     if (!key) return 1;
//     if ((float) (table->count + 1) / table->size > table->load_factor) open_hash_table_rehash (table, open_hash_table_add);
//     size_t curr_idx = table->size + 1;
//     void *curr_key = key;
//     void *second_key = NULL;
//     void **arr = table->arr;


//     for (unsigned i = 0; i < table->max_iterations; i++)
//     {
//         curr_idx = table->hash_f1 (curr_key);
//         if (arr [curr_idx] == EMPTY ||)
//         {
//             arr [curr_idx] = curr_key;
//             return 0;
//         }
//         curr_idx = table->hash_f2 (curr_key);
//         second_key = arr [curr_idx];
//         arr [curr_idx] = curr_key;
//         if (second_key != EMPTY)
//         {

//         }


//     }
// }


// int open_hash_table_add_cuckoo (open_hash_table_t *table, void *key)
// {
//     if (!table || !key) return 1;

//     if (open_hash_table_search_cuckoo (table, key) != -1) return 0;

//     if ((float) (table->count + 1) / table->size > table->load_factor) 
//     {
//         open_hash_table_rehash (table, open_hash_table_add_cuckoo);
//     }

//     void *curr_key = key;
//     size_t curr_idx = 0;
//     void *second_key = NULL;

//     for (unsigned i = 0; i < table->max_iterations; i++)
//     {
//         curr_idx = table->hash_f1 (curr_key) % table->size;
//         if (table->arr [curr_idx] == EMPTY || table->arr [curr_idx] == DELETED)
//         {
//             table->arr [curr_idx] = curr_key;
//             table->count++;
//             return 0;
//         }

//         curr_idx = table->hash_f2 (curr_key) % table->size;
        
//         second_key = table->arr [curr_idx];
//         table->arr [curr_idx] = curr_key;
        
//         if (second_key == EMPTY || second_key == DELETED)
//         {
//             table->count++;
//             return 0;
//         }
//         curr_key = second_key;
//     }

//     open_hash_table_rehash (table, open_hash_table_add_cuckoo);
//     return open_hash_table_add_cuckoo (table, curr_key);
// }

// unsigned idx_func_linear (open_hash_table_t *table, void *key, unsigned cur_step)
// {
//     return (table->hash_f1 (key) + cur_step);
// }

// unsigned idx_func_quadratic (open_hash_table_t *table, void *key, unsigned cur_step)
// {
//     return (table->hash_f1 (key) + (cur_step * cur_step + cur_step) / 2);
// }

// unsigned idx_func_double (open_hash_table_t *table, void *key, unsigned cur_step)
// {
//     return (table->hash_f1 (key) + table->hash_f2 (key) * cur_step);
// }
