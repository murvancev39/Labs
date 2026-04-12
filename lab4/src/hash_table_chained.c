#include "hash_table_chained.h"

chained_hash_table_t *chained_hash_table_ctr (size_t size)
{
    chained_hash_table_t *table = (chained_hash_table_t *) malloc (1 * sizeof (chained_hash_table_t));
    table->nodes_arr = (node_t **) calloc (size, sizeof (node_t *));
    table->collision_arr = (unsigned *) calloc (size, sizeof (unsigned));
    table->size = size;
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

int chained_hash_table_add (chained_hash_table_t *table, void *key, unsigned idx)
{
    table->collision_arr [idx]++;
    node_t *node = (node_t *) malloc (1 * sizeof (node_t));
    if (!node) return 0;
    node->key = key;
    node->next = table->nodes_arr [idx];
    table->nodes_arr [idx] = node;
    table->count++;
    return 1;
}

int chained_hash_table_unsigned_search (chained_hash_table_t *table, void *key, unsigned hash_f_val)
{
    unsigned uns_key = *((unsigned *) key);
    node_t *node = table->nodes_arr [hash_f_val];
    while (node != NULL)
    {
        if (*((unsigned *) node->key) == uns_key) return 1;
        node = node->next;
    }
    return 0;
}

int chained_hash_table_unsigned_delete (chained_hash_table_t *table, void *key, unsigned hash_f_val)
{
    unsigned uns_key = *((unsigned *) key);
    node_t *prev_node = table->nodes_arr [hash_f_val];
    if (prev_node == NULL) return 0;
    node_t *node = prev_node->next;

    if (*(unsigned *) prev_node->key == uns_key)
    {
        table->nodes_arr [hash_f_val] = node;
        free (prev_node);
        table->count--;
        return 1;
    }

    while (node != NULL)
    {
        if (*((unsigned *) node->key) == uns_key)
        {
            prev_node->next = node->next;
            free (node);
            table->count--;
            return 1;
        }
        prev_node = node;
        node = node->next;
    }
    return 0;
}

void rehash (chained_hash_table_t *table, int (*add_func)(chained_hash_table_t *, void *, unsigned))
{
    size_t old_size = table->size;
    node_t **old_nodes = table->nodes_arr;
    unsigned *old_collisions = table->collision_arr;

    table->size *= 2;
    table->count = 0;

    table->nodes_arr = (node_t **) calloc (table->size, sizeof (node_t *));
    table->collision_arr = (unsigned *) calloc (table->size, sizeof (unsigned));

    for (size_t i = 0; i < old_size; i++)
    {
        node_t *curr = old_nodes [i];
        while (curr)
        {
            unsigned key_val = *((unsigned *) curr->key);
            unsigned new_idx = table->hash_f (key_val) % table->size;

            add_func (table, curr->key, new_idx);

            node_t *to_free = curr;
            curr = curr->next;
            free (to_free); 
        }
    }
    free (old_nodes);
    free (old_collisions);
}