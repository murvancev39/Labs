#ifndef GRAPHS_H
#define GRAPHS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Edge_t 
{
    int idx;
    unsigned weight;
    struct Edge_t *next;
} edge_t;

typedef struct Graph_t 
{
    int nodes_count;
    int edges_count;
    edge_t **nodes_arr;
} graph_t;

void     free_graph            (graph_t *graph);
graph_t *create_graph          (unsigned nodes_count);
int      generate_random_graph (graph_t *graph, int num_edges, unsigned max_weight);
int      add_edge              (graph_t *graph, unsigned from, unsigned to, unsigned weight);


#endif