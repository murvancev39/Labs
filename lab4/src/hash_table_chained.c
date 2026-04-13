#include "hash_table_chained.h"

chained_hash_table_t *chained_hash_table_ctr (size_t size, float load_factor,
                                unsigned (*hash_f) (void *), int (*cmp) (void *, void *))
{
    chained_hash_table_t *table = (chained_hash_table_t *) malloc (1 * sizeof (chained_hash_table_t));
    table->nodes_arr = (node_t **) calloc (size, sizeof (node_t *));
    table->collision_arr = (unsigned *) calloc (size, sizeof (unsigned));
    table->load_factor = load_factor;
    table->count = 0;
    table->size = size;
    table->hash_f = hash_f;
    table->cmp = cmp;
    return table;   
}

void chained_hash_table_clean (chained_hash_table_t *table)
{
    node_t **nodes = table->nodes_arr;
    unsigned *collision_arr = table->collision_arr;
    for (size_t i = 0; i < table->size; i++)
    {
        nodes_dtr (nodes [i]);
        nodes [i] = NULL;
        collision_arr [i] = 0;
    }
    return;
}

void chained_hash_table_dtr (chained_hash_table_t *table)
{
    node_t **nodes = table->nodes_arr;
    for (size_t i = 0; i < table->size; i++)
    {
        nodes_dtr (nodes [i]);
    }
    free (table->nodes_arr);
    free (table->collision_arr);
    free (table);
    return;
}

void nodes_dtr (node_t *node)
{
    if (!node) return;

    node_t *cur_node = node;
    node_t *next_node = NULL;
    while (cur_node != NULL)
    {
        next_node = cur_node->next;
        free (cur_node);
        cur_node = next_node;
    }
}

int chained_hash_table_add (chained_hash_table_t *table, void *key)
{
    if ((!table) || (!key)) return 0;
    if ((table->load_factor != 0) && (((float) table->count) / ((float) table->size) > table->load_factor))
    {
        rehash (table, chained_hash_table_add);
    } 
    unsigned idx = table->hash_f (key) % table->size;

    table->collision_arr [idx]++;
    node_t *node = (node_t *) malloc (1 * sizeof (node_t));

    if (!node) return 0;

    node->key = key;
    node->next = table->nodes_arr [idx];
    table->nodes_arr [idx] = node;
    table->count++;
    return 1;
}

int chained_hash_table_search (chained_hash_table_t *table, void *key)
{
    node_t *node = table->nodes_arr [table->hash_f (key) % table->size];
    while (node != NULL)
    {
        if (!table->cmp (key, node->key)) return 1;
        node = node->next;
    }
    return 0;
}

int chained_hash_table_delete (chained_hash_table_t *table, void *key)
{
    unsigned idx = table->hash_f (key) % table->size;
    node_t *prev_node = table->nodes_arr [idx];
    if (prev_node == NULL) return 0;
    node_t *node = prev_node->next;

    if (!table->cmp (key, prev_node->key))
    {
        table->nodes_arr [idx] = node;
        free (prev_node);
        table->count--;
        table->collision_arr [idx]--;
        return 1;
    }

    while (node != NULL)
    {
        if (!table->cmp (key, node->key))
        {
            prev_node->next = node->next;
            free (node);
            table->count--;
            table->collision_arr [idx]--;
            return 1;
        }
        prev_node = node;
        node = node->next;
    }
    return 0;
}

void rehash (chained_hash_table_t *table, int (*add_func) (chained_hash_table_t *, void *))
{
    size_t old_size = table->size;
    node_t **old_nodes = table->nodes_arr;
    unsigned *old_collisions = table->collision_arr;
    node_t *curr = NULL;
    node_t *to_free;

    table->size *= 2;
    table->count = 0;

    table->nodes_arr = (node_t **) calloc (table->size, sizeof (node_t *));
    table->collision_arr = (unsigned *) calloc (table->size, sizeof (unsigned));

    for (size_t i = 0; i < old_size; i++)
    {
        curr = old_nodes [i];
        while (curr)
        {
            add_func (table, curr->key);

            to_free = curr;
            curr = curr->next;
            free (to_free); 
        }
    }
    free (old_nodes);
    free (old_collisions);
}