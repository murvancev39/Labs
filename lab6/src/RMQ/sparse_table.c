#include "sparse_table.h"

void *create_v_n (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    sparse_t *table = (sparse_t *) calloc (1, sizeof (sparse_t));
    if (!table) return NULL;

    table->n = len;
    unsigned logn = 0;
    while ( (unsigned) (1 << logn) <= len)
    {
        logn++;
    }
    table->logn = logn;

    char *lg_arr = (char *) malloc ((len + 1) * sizeof (char));
    table->lg_arr = lg_arr;
    if (!lg_arr) return free_in_create (table, 0);
    lg_arr [0] = 0;
    lg_arr [1] = 0;
    for (unsigned i = 2; i <= len; i++)
    {
        lg_arr [i] = lg_arr [i / 2] + 1;
    }

    unsigned **table_arr = (unsigned **) malloc (table->n *sizeof (unsigned *));
    if (!table_arr) return free_in_create (table, 0);
    for (unsigned i = 0; i < table->n; i++)
    {
        table_arr [i] = malloc (logn * sizeof (unsigned));
        if (!(table_arr [i])) return free_in_create (table, i);
        table_arr [i][0] = arr [i];
    }
    table->table = table_arr;

    unsigned left_min = 0;
    unsigned right_min = 0;

    for (unsigned char log = 1; (unsigned) log < logn; (unsigned) log++)
    {
        for (unsigned i = 0; i + (1 << (unsigned) log) <= len; i++)
        {
            left_min  = table_arr [i] [(unsigned) log - 1];
            right_min = table_arr [i + (1 << ((unsigned) log - 1))] [(unsigned) log - 1];

            table_arr [i] [(unsigned) log] = min (left_min, right_min);
        }
    }

    return table;
}

void *create_v_logn (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    sparse_t *table = (sparse_t *) calloc (1, sizeof (sparse_t));
    if (!table) return NULL;

    table->n = len;
    unsigned logn = 0;
    while ((unsigned) (1 << logn) <= len)
    {
        logn++;
    }
    table->logn = logn;

    char *lg_arr = (char *) malloc ((len + 1) * sizeof (char));
    table->lg_arr = lg_arr;
    if (!lg_arr) return free_in_create (table, 0);
    lg_arr [0] = 0;
    lg_arr [1] = 0;
    for (unsigned i = 2; i <= len; i++)
    {
        lg_arr [i] = lg_arr [i / 2] + 1;
    }

    unsigned **table_arr = (unsigned **) malloc (table->logn *sizeof (unsigned *));
    if (!table_arr) return free_in_create (table, 0);
    for (unsigned i = 0; i < logn; i++)
    {
        table_arr [i] = malloc (len * sizeof (unsigned));
        if (!(table_arr [i])) return free_in_create (table, i);
    }
    table->table = table_arr;
    
    // [i; i - 1 + 2^0] = [i; i]
    for (unsigned i = 0; i < len; i++) table_arr [0][i] = arr [i];
    unsigned left_min = 0;
    unsigned right_min = 0;

    for (unsigned char log = 1; (unsigned) log < logn; (unsigned) log++)
    {
        for (unsigned i = 0; i + (1 << (unsigned) log) <= len; i++)
        {
            // [i; i - 1 + 2^((unsigned) log - 1)]
            left_min  = table_arr [(unsigned) log - 1] [i];
            // [i + 2^((unsigned) log - 1); i - 1 + 2*2^((unsigned) log - 1)]]
            right_min = table_arr [(unsigned) log - 1] [i + (1 << ((unsigned) log - 1))];

            // [i; i - 1 + 2^(unsigned) log]
            table_arr [(unsigned) log] [i] = min (left_min, right_min);
        }
    }

    return table;
}

long long rmq_v_n (sparse_t *table, unsigned left, unsigned right)
{
    unsigned len = right - left + 1;

    char log = table->lg_arr [len];

    unsigned left_min  = table->table [left] [(unsigned) log];
    unsigned right_min = table->table [right - (1 << (unsigned) log) +1] [(unsigned) log];
    return (long long) min (left_min, right_min);
}

long long rmq_v_logn (sparse_t *table, unsigned left, unsigned right)
{
    
    unsigned len = right - left + 1;

    char log = table->lg_arr [len];

    unsigned left_min  = table->table [(unsigned) log] [left];
    unsigned right_min = table->table [(unsigned) log] [right - (1 << (unsigned) log) +1];
    return (long long) min (left_min, right_min);
}

sparse_t *free_in_create (sparse_t *table, unsigned error_string_idx)
{
    if (!table) return NULL;

    if (table->table)
    {
        if (error_string_idx != 0)
        {
            for (unsigned i = 0; i < error_string_idx; i++)
            {
                free (table->table [i]);
            }
        }
        free (table->table);
    }

    if (table->lg_arr) free (table->lg_arr);

    if (table) free (table);
    return NULL;
}

unsigned min (unsigned first, unsigned second)
{
    if (first > second) return second;
    return first;
}

void destruct_v_n (sparse_t *table)
{
    if (!table) return;

    if (table->table)
    {
        for (unsigned i = 0; i < table->n; i++)
        {
            if (table->table [i]) free (table->table [i]);
        }
        free (table->table);
    }

    if (table->lg_arr) free (table->lg_arr);
    
    free (table);
    return;
}

void destruct_v_logn (sparse_t *table)
{
    if (!table) return;

    if (table->table)
    {
        for (unsigned i = 0; i < table->logn; i++)
        {
            if (table->table [i]) free (table->table [i]);
        }
        free (table->table);
    }

    if (table->lg_arr) free (table->lg_arr);

    free (table);
    return;
}