#include "hash_table_open.h"

open_hash_table_t *open_hash_table_ctr (size_t size, float load_factor)
{
    open_hash_table_t *table = (open_hash_table_t *) calloc (1, sizeof (open_hash_table_t));
    table->arr = (unsigned *) calloc (size, sizeof (unsigned));
    table->count = 0;
    table->size = size;
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

void open_hash_table_rehash (open_hash_table_t *table)
{
    size_t old_size = table->size;
    void **old_arr = table->arr;

    table->size *= 2;
    table->arr = (void **) calloc (table->size, sizeof (void *));
    
    table->count = 0;

    for (size_t i = 0; i < old_size; i++)
    {
        if (old_arr [i] != EMPTY && (old_arr [i] != DELETED)) open_hash_table_add (table, old_arr [i]);
    }

    free(old_arr);
}

// ------------------------------------------------------------------------------------------
// LINEAR
// ------------------------------------------------------------------------------------------
int open_hash_table_add (open_hash_table_t *table, void *key)
{
    if ((float) (table->count + 1) / table->size > table->load_factor) open_hash_table_rehash (table);

    size_t h = table->hash_f1 (table, key);

    for (size_t i = 0; i < table->size; i++)
    {
        size_t curr_idx = (h + i) % table->size;
        if (table->arr [curr_idx] == key) return 0;

        if (table->arr [curr_idx] == empty || table->arr [curr_idx] == deleted)
        {
            table->arr [curr_idx] = key;
            table->count++;
            return 1;
        }
    }
    return -1;
}

// int open_hash_table_search_linear (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + i) % table->size;
//         if (table->arr [curr_idx] == key) return (int) curr_idx;

//         if (table->arr [curr_idx] == empty) return -1;
//     }
//     return -1;
// }

// int open_hash_table_delete_linear (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + i) % table->size;
//         if (table->arr [curr_idx] == key)
//         {
//             table->count--;
//             table->arr [curr_idx] = deleted;
//             return 1;
//         }

//         if (table->arr [curr_idx] == empty) return 0;
//     }
//     return 0;
// }


// // ------------------------------------------------------------------------------------------
// // QUADRATIC
// // ------------------------------------------------------------------------------------------

// int open_hash_table_add_quadratic (open_hash_table_t *table, unsigned key)
// {
//     if ((float)(table->count + 1) / table->size > table->load_factor) open_hash_table_rehash (table, open_hash_table_add_quadratic);

//     size_t h = hash (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + (i*i + i) / 2) % table->size;
//         if (table->arr [curr_idx] == key) return 0;

//         if (table->arr [curr_idx] == empty || table->arr [curr_idx] == deleted)
//         {
//             table->arr [curr_idx] = key;
//             table->count++;
//             return 1;
//         }
//     }
//     return -1;
// }

// int open_hash_table_search_quadratic (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + (i*i + i) / 2) % table->size;
//         if (table->arr [curr_idx] == key) return (int) curr_idx;

//         if (table->arr [curr_idx] == empty) return -1;
//     }
//     return -1;
// }

// int open_hash_table_delete_quadratic (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + (i*i + i) / 2) % table->size;
        
//         if (table->arr [curr_idx] == key)
//         {
//             table->count--;
//             table->arr [curr_idx] = deleted;
//             return 1;
//         }

//         if (table->arr [curr_idx] == empty) return 0;
//     }
//     return 0;
// }

// // ------------------------------------------------------------------------------------------
// // DOUBLE
// // ------------------------------------------------------------------------------------------


// int open_hash_table_add_double (open_hash_table_t *table, unsigned key)
// {
//     if ((float)(table->count + 1) / table->size > table->load_factor) open_hash_table_rehash (table, open_hash_table_add_double);

//     size_t h = hash (key);
//     size_t h_2 = hash_2 (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + i * h_2) % table->size;
//         if (table->arr [curr_idx] == key) return 0;

//         if (table->arr [curr_idx] == empty || table->arr [curr_idx] == deleted)
//         {
//             table->arr [curr_idx] = key;
//             table->count++;
//             return 1;
//         }
//     }
//     return -1;
// }

// int open_hash_table_search_double (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);
//     size_t h_2 = hash_2 (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + i * h_2) % table->size;
//         if (table->arr [curr_idx] == key) return (int) curr_idx;

//         if (table->arr [curr_idx] == empty) return -1;
//     }
//     return -1;
// }

// int open_hash_table_delete_double (open_hash_table_t *table, unsigned key)
// {
//     size_t h = hash (key);
//     size_t h_2 = hash_2 (key);

//     for (size_t i = 0; i < table->size; i++)
//     {
//         size_t curr_idx = (h + i * h_2) % table->size;
        
//         if (table->arr [curr_idx] == key)
//         {
//             table->count--;
//             table->arr [curr_idx] = deleted;
//             return 1;
//         }

//         if (table->arr [curr_idx] == empty) return 0;
//     }
//     return 0;
// }