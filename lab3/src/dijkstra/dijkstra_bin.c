#include "bin_dijkstra.h"

void heap_init (Heap *heap, size_t size)
{
    heap->capacity = 1;
    heap->size = 0;
    heap->arr = (bin_node *) calloc (heap->capacity, sizeof (bin_node));
    heap->idx_arr = (unsigned *) malloc (size * sizeof (unsigned));
    for (size_t i = 0; i < size; i++)
    {
        heap->idx_arr [i] = NOT_IN_HEAP;
    }
    return;
}
 
void insert (Heap *heap, unsigned x, int idx)
{
    if (heap->size >= heap->capacity)
    {
        heap->capacity *= 2;
        heap->arr = (bin_node *) realloc (heap->arr, heap->capacity * sizeof (bin_node));
    }

    heap->arr [heap->size].val = x;
    heap->arr [heap->size].idx = idx;

    heap->idx_arr [idx] = heap->size;

    sift_up (heap, heap->size);

    heap->size++;    
    return;
}

void sift_up (Heap* heap, size_t idx)
{
    bin_node cur_node = heap->arr [idx];
    size_t dad = 0;
    bin_node dad_node = {};

    while (idx != 0)
    {
        dad = (idx - 1) / 2;
        dad_node = heap->arr [dad];

        if (dad_node.val > cur_node.val)
        {
            heap->arr [idx] = dad_node;
            heap->idx_arr [dad_node.idx] = idx;
            idx = dad;
        }
        else
        {
            break;
        }
    }
    heap->arr [idx] = cur_node;
    heap->idx_arr [cur_node.idx] = idx;
    return;
}

void bottom_up_sift_down (Heap *heap, size_t idx)
{
    if (idx >= heap->size)
    {
        return;
    }

    size_t left = idx * 2 + 1;
    size_t right = idx * 2 + 2;
    size_t dad = idx;
    bin_node dad_node = heap->arr [dad];
    bin_node left_node = {};
    bin_node right_node = {};


    while (right < heap->size)
    {    
        left_node = heap->arr [left];
        right_node = heap->arr [right];
        if (left_node.val < right_node.val)
        {
            heap->arr [dad] = left_node;
            heap->idx_arr[left_node.idx] = dad;
            dad = left;
        }
        else
        {
            heap->arr [dad] = right_node;
            heap->idx_arr[right_node.idx] = dad;
            dad = right;
        }
        left = dad * 2 + 1;
        right = dad * 2 + 2;
    }

    if (left < heap->size)
    {
        heap->arr [dad] = heap->arr [left];
        heap->idx_arr[heap->arr[dad].idx] = dad;
        dad = left;
    }

    heap->arr [dad] = dad_node;
    heap->idx_arr[dad_node.idx] = dad;

    sift_up (heap, dad);
    return;
}


void swap (Heap *heap, size_t i, size_t j)
{
    bin_node swap_val = heap->arr [i];
    heap->arr [i] = heap->arr [j];
    heap->arr [j] =  swap_val;

    heap->idx_arr [heap->arr[i].idx] = i;
    heap->idx_arr [heap->arr[j].idx] = j;
}

void new_lower_key (Heap *heap, int idx, unsigned new_val)
{
    unsigned pos = heap->idx_arr [idx];
    
    heap->arr [pos].val = new_val;
    
    sift_up (heap, pos);
    
    return;
}

bin_node extract_min (Heap *heap)   
{
    bin_node min_node = heap->arr [0];
    heap->size--;

    heap->idx_arr [min_node.idx] = -1; 

    heap->arr [0] = heap->arr [heap->size];
    
    if (heap->size > 0)
    {
        heap->idx_arr [heap->arr [0].idx] = 0;
        bottom_up_sift_down (heap, 0);
    }

    return min_node;
}

void dijkstra (Graph *graph, int start_node, unsigned *shortest_distances, Heap *heap)
{
    for (int i = 0; i < graph->nodes_count; i++)
    {
        shortest_distances [i] = UINT_MAX;
        heap->idx_arr [i] = NOT_IN_HEAP;
    }

    shortest_distances [start_node] = 0;
    insert (heap, 0, start_node);
    // int i = 0;
    while (heap->size > 0)
    {
        bin_node min_node = extract_min (heap);
        int v = min_node.idx;
        // printf ("%d! %d %d \n", i, min_node.idx, min_node.val);
        // i++;
        heap->idx_arr [v] = VISITED;

        Edge *edge = graph->nodes_arr [v];
        while (edge != NULL)
        {
            int idx = edge->idx;
            unsigned weight = edge->weight;

            if  (shortest_distances [v] != UINT_MAX && 
                (shortest_distances [v] + weight < shortest_distances [idx]) && 
                (heap->idx_arr [idx] != VISITED))
            {
                shortest_distances [idx] = shortest_distances [v] + weight;

                if (heap->idx_arr [idx] == NOT_IN_HEAP)
                {
                    insert (heap, shortest_distances [idx], idx);
                }
                else
                {
                    new_lower_key (heap, idx, shortest_distances [idx]);
                }
            }
            edge = edge->next;
        }
    }
}
