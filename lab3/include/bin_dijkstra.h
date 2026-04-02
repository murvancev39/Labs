#ifndef BIN_DIJKSTRA_H 
#define BIN_DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "graphs.h"

#define NOT_IN_HEAP 0xFFFFFFFF
#define VISITED     0xFFFFFFFE

typedef struct
{
    unsigned val;
    unsigned idx;
} bin_node;


struct heap
{
    bin_node *arr;
    unsigned *idx_arr;
    size_t capacity;
    size_t size;
};

typedef struct heap Heap;

void heap_init (Heap *heap, size_t size);
void insert (Heap *heap, unsigned x, int idx);
void sift_up (Heap* heap, size_t idx);
void bottom_up_sift_down (Heap *heap, size_t idx);
void swap (Heap *heap, size_t i, size_t j);
bin_node extract_min (Heap *heap);
void dijkstra (Graph *graph, int start_node, unsigned *shortest_distances, Heap *heap);
void new_lower_key (Heap *heap, int idx, unsigned new_val);


#endif