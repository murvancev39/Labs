#include "graphs.h"


Graph* create_graph (int nodes_count)
{
    Graph *graph = (Graph *) malloc (sizeof (Graph));
    graph->nodes_count = nodes_count;
    graph->edges_count = 0;
    
    graph->nodes_arr = (Edge **) calloc (nodes_count, sizeof (Edge *));
    
    return graph;
}

void add_edge (Graph *graph, int from, int to, unsigned weight)
{
    Edge *new_edge = (Edge *) malloc (sizeof (Edge));
    
    new_edge->idx = to;
    new_edge->weight = weight;
    
    new_edge->next = graph->nodes_arr [from];
    graph->nodes_arr [from] = new_edge;
    
    graph->edges_count++;
    return;
}

void free_graph (Graph *graph)
{
    for (int i = 0; i < graph->nodes_count; i++) 
    {
        Edge *current = graph->nodes_arr [i];
        while (current != NULL) 
        {
            Edge *prev = current;
            current = current->next;
            free (prev);
        }
    }
    free (graph->nodes_arr);
    free (graph);
}

void generate_random_graph (Graph *graph, int num_edges, unsigned max_weight)
{
    srand (time (NULL));

    // unsigned sum_len = 0;

    for (int i = 0; i < graph->nodes_count - 1; i++)
    { //это чтоб сызяность была
        unsigned weight = (rand () % max_weight) + 1;
        // sum_len += weight;
        add_edge (graph, i, i + 1, weight);
    }

    int remaining = num_edges - (graph->edges_count - 1);
    // printf ("[sum_len %d| %d| %d]", sum_len, remaining, graph->edges_count - 1);
    for (int i = 0; i < remaining; i++)
    {
        int from = rand () % graph->nodes_count;
        int to = rand () % graph->nodes_count;
        if (from == to)
        {// бех петель
            i--;
            continue;
        }
        
        unsigned w = (rand () % max_weight) + 1;
        add_edge (graph, from, to, w);
    }
}
