#include "graphs.h"


graph_t* create_graph (unsigned nodes_count)
{
    if (!nodes_count) return NULL;

    graph_t *graph = (graph_t *) malloc (sizeof (graph_t));
    if (!graph) return NULL;

    graph->edges_count = 0;
    
    graph->nodes_arr = (edge_t **) calloc (nodes_count, sizeof (edge_t *));
    if (!graph->nodes_arr) 
    {
        free (graph);
        return NULL;
    }

    graph->nodes_count = nodes_count;
    
    return graph;
}

int add_edge (graph_t *graph, unsigned from, unsigned to, unsigned weight)
{
    if (!graph) return 1;

    edge_t *new_edge = (edge_t *) malloc (sizeof (edge_t));
    if (!new_edge) return 1;
    
    new_edge->idx = to;
    new_edge->weight = weight;
    
    new_edge->next = graph->nodes_arr [from];
    graph->nodes_arr [from] = new_edge;
    
    graph->edges_count++;
    return 0;
}

void free_graph (graph_t *graph)
{
    if (!graph) return;

    for (int i = 0; i < graph->nodes_count; i++) 
    {
        edge_t *current = graph->nodes_arr [i];
        while (current != NULL) 
        {
            edge_t *prev = current;
            current = current->next;
            free (prev);
        }
    }
    free (graph->nodes_arr);
    free (graph);
}

int generate_random_graph (graph_t *graph, int num_edges, unsigned max_weight)
{
    if (!graph)     return 1;
    if (!num_edges) return 0;

    // для связности
    for (int i = 0; i < graph->nodes_count - 1; i++)
    {
        unsigned weight = (rand () % max_weight) + 1;
        if (add_edge (graph, i, i + 1, weight)) return 1;
    }

    int remaining = num_edges - (graph->edges_count - 1);

    for (int i = 0; i < remaining; i++)
    {
        int from = rand () % graph->nodes_count;
        int to = rand () % graph->nodes_count;
        
        if (from == to)
        {
            i--;
            continue;
        }
        
        unsigned w = (rand () % max_weight) + 1;
        add_edge (graph, from, to, w);
    }
    return 0;
}
