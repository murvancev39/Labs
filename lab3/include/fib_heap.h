#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include <time.h>
#include "graphs.h"

#define NOT_IN_HEAP NULL
#define VISITED     ((void *) 1)

enum yea_or_not
{
    no = 0,
    yea = 1,
};

typedef struct Fib_Node 
{
    unsigned elem;
    int degree;
    struct Fib_Node *parent;
    struct Fib_Node *child;
    struct Fib_Node *right_bro;
    struct Fib_Node *left_bro;
    int son_is_dead;
    int dijkstra_id;
} fib_node;

typedef struct Fib_Heap 
{
    fib_node *min;
    int n;
} fib_heap;

fib_node **idx_arr_init (size_t size);

void destruct_nodes (fib_node *node);
fib_node *insert_val (fib_heap *heap, unsigned val, int dijkstra_id);
unsigned get_min (fib_heap *heap);
int extract_min (fib_heap *heap, fib_node **idx_arr);
void new_lower_key (fib_heap *heap, fib_node *node, unsigned val);

void merge_lists (fib_node *node_1, fib_node *node_2);
void merge_heaps (fib_heap *heap_1, fib_heap *heap_2);
void consolidate (fib_heap *heap);
void fill_heap_by_nodes_arr (fib_heap *heap, fib_node **fib_arr, unsigned len);
fib_node *link (fib_node *node_1, fib_node *node_2);
void insert_node (fib_heap *heap, fib_node *new_node);
void cut (fib_node *node);
void cut_rec (fib_heap *heap, fib_node *node);

void dijkstra (graph_t *graph, int start_node, unsigned *shortest_distances, fib_heap *heap, fib_node **idx_arr);

#endif
