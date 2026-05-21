#include "sparse_table.h"

static unsigned get_log2 (unsigned len)
{
    if (len == 0) return 0;

    unsigned logn = 0;
    while ((unsigned) (1 << logn) <= len)
    {
        logn++;
    }
    return logn;
}

static void init_logs (char *lg_arr, unsigned len)
{
    if (!lg_arr) return;
    lg_arr [0] = 0;
    lg_arr [1] = 0;
    for (unsigned i = 2; i <= len; i++)
    {
        lg_arr [i] = lg_arr [i / 2] + 1;
    }
}

static int fill_table_n (sparse_t *table, unsigned *arr)
{
    unsigned **table_arr = (unsigned **) malloc (table->n * sizeof (unsigned *));
    if (!table_arr) return 0;
    table->table = table_arr;

    for (unsigned i = 0; i < table->n; i++)
    {
        table_arr [i] = malloc (table->logn * sizeof (unsigned));
        if (!(table_arr [i])) return (int) i;
        table_arr [i][0] = arr [i];
    }

    for (unsigned char log = 1; (unsigned) log < table->logn; (unsigned) log++)
    {
        for (unsigned i = 0; i + (1 << (unsigned) log) <= table->n; i++)
        {
            unsigned left  = table_arr [i] [(unsigned) log - 1];
            unsigned right = table_arr [i + (1 << ((unsigned) log - 1))] [(unsigned) log - 1];
            table_arr [i] [(unsigned) log] = (left < right) ? left : right;
        }
    }
    return -1;
}

void *create_v_n (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    sparse_t *table = (sparse_t *) calloc (1, sizeof (sparse_t));
    if (!table) return NULL;

    table->n = len;
    unsigned logn = get_log2 (len);
    table->logn = logn;

    char *lg_arr = (char *) malloc ((len + 1) * sizeof (char));
    if (!lg_arr) return free_in_create (table, 0);

    table->lg_arr = lg_arr;
    init_logs (lg_arr, len);

    int res = fill_table_n (table, arr);
    if (res != -1) return free_in_create (table, (unsigned) res);

    return table;
}

static int fill_table_logn (sparse_t *table, unsigned *arr)
{
    if (!table) return 0;

    unsigned **table_arr = (unsigned **) malloc (table->logn * sizeof (unsigned *));
    if (!table_arr) return 0;
    
    table->table = table_arr;

    for (unsigned log = 0; log < table->logn; log++)
    {
        table_arr [log] = malloc (table->n * sizeof (unsigned));
        if (!(table_arr [log])) return (int) log + 1;
    }

    for (unsigned i = 0; i < table->n; i++)
    {
        table_arr [0][i] = arr [i];
    }

    for (unsigned log = 1; log < table->logn; log++)
    {
        for (unsigned i = 0; i + (1 << log) <= table->n; i++)
        {
            unsigned left  = table_arr [log - 1] [i];
            unsigned right = table_arr [log - 1] [i + (1 << (log - 1))];
            table_arr [log] [i] = (left < right) ? left : right;
        }
    }
    
    return -1;
}

void *create_v_logn (unsigned *arr, unsigned len)
{
    if (!arr || !len) return NULL;

    sparse_t *table = (sparse_t *) calloc (1, sizeof (sparse_t));
    if (!table) return NULL;

    table->n = len;
    table->logn = get_log2 (len);

    char *lg_arr = (char *) malloc ((len + 1) * sizeof (char));
    if (!lg_arr) return free_in_create (table, 0);

    table->lg_arr = lg_arr;
    init_logs (lg_arr, len);

    int res = fill_table_logn (table, arr);
    if (res != -1) return free_in_create (table, (unsigned) res);

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
    return (first > second) ? second : first;
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