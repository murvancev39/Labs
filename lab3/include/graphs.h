#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Edge 
{
    int idx;
    unsigned weight;
    struct Edge *next;
} Edge;

typedef struct Graph 
{
    int nodes_count;
    int edges_count;
    Edge **nodes_arr;
} Graph;

Graph* create_graph (int nodes_count);
void add_edge (Graph *graph, int from, int to, unsigned weight);
void free_graph (Graph *graph);
void generate_random_graph (Graph *graph, int num_edges, unsigned max_weight);


#endif