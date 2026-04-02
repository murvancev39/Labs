#include "binom_dijkstra.h"
#include <string.h>

int main (int argc, char *argv[])
{    
    long long time = 0;
    double res_time = 0;

    int flag_S = 0;
    int flag_D = 0;
    for (int k = 1; k < argc; k++)
    {
        if (!strcmp(argv[k], "-D")) flag_D = 1;
        if (!strcmp(argv[k], "-S")) flag_S = 1;
    }

    if (flag_D == 1)
    {
        for (int i = 1000; i <= 5000; i += 500)
        {
            time = 0;
            for (int z = 0; z < 5; z++)
            {
                Graph *graph = create_graph (i);
                generate_random_graph (graph, i * (i / 4), 1000000);
                unsigned *shortest_distances = (unsigned *) malloc (sizeof (*shortest_distances) * i);
                
                binom_heap heap = {};
                heap.child = NULL;
                
                size_t size = i;
                binom_heap **idx_arr = idx_arr_init (size);
                
                time -= clock ();
                dijkstra (graph, 0, shortest_distances, &heap, idx_arr);
                time += clock ();
                
                free (shortest_distances);
                free_graph (graph);
                destroy_heap (&heap);
                free (idx_arr);
            }
            
            res_time = time;
            res_time /= 5;
            printf ("%d %lf\n", i, res_time / CLOCKS_PER_SEC);
            
        }
    }

    if (flag_S == 1)
    {
        for (int i = 100000; i <= 500000; i += 50000)
        {
            time = 0;
            for (int z = 0; z < 5; z++)
            {
                Graph *graph = create_graph (i);
                generate_random_graph (graph, i * 5, 1000000);
                unsigned *shortest_distances = (unsigned *) malloc (sizeof (*shortest_distances) * i);
                
                binom_heap heap = {};
                heap.child = NULL;
                
                size_t size = i;
                binom_heap **idx_arr = idx_arr_init (size);
                
                time -= clock ();
                dijkstra (graph, 0, shortest_distances, &heap, idx_arr);
                time += clock ();
                
                free (shortest_distances);
                free_graph (graph);
                destroy_heap (&heap);
                free (idx_arr);
            }
            
            res_time = time;
            res_time /= 5;
            printf ("%d %lf\n", i, res_time / CLOCKS_PER_SEC);
            
        }
    }    
    return 0;
}
