#include "bin_dijkstra.h"

void heap_init (Heap *heap, size_t size, int (*cmp) (void *, void *))
{
    if (!heap || !cmp) return;

    heap->cmp = cmp;

    heap->capacity = 1;
    heap->size = 0;
    heap->arr = (bin_node *) calloc (heap->capacity, sizeof (bin_node));
    if (!heap->arr) return;

    heap->idx_arr = (unsigned *) malloc (size * sizeof (unsigned));
    if (!heap->idx_arr)
    {
        free (heap->arr);
        heap->arr = NULL;
        return;
    }
    for (size_t i = 0; i < size; i++)
    {
        heap->idx_arr [i] = NOT_IN_HEAP;
    }
    return;
}
 
void insert (Heap *heap, void * x, int idx)
{
    if (!heap || !x) return;
    if (heap->size >= heap->capacity)
    {
        bin_node *new_arr = (bin_node *) realloc (heap->arr, heap->capacity * 2 * sizeof (bin_node));
        if (!new_arr) return;
        heap->capacity *= 2;
        heap->arr = new_arr;
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
    if (!heap) return;
    bin_node cur_node = heap->arr [idx];
    size_t dad = 0;
    bin_node dad_node = {};

    while (idx != 0)
    {
        dad = (idx - 1) / 2;
        dad_node = heap->arr [dad];

        if (heap->cmp (dad_node.val, cur_node.val) > 0)
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
    if (!heap) return;
    if (idx >= heap->size) return;

    size_t dad = idx;
    bin_node dad_node = heap->arr [dad]; 

    while (dad * 2 + 1 < heap->size)
    {
        size_t left = get_left_child (dad);
        size_t right = get_right_child (dad);
        size_t child = left;

        if (right < heap->size && heap->cmp (heap->arr [right].val, heap->arr [left].val) < 0)
        {
            child = right;
        }

        heap->arr [dad] = heap->arr [child];
        heap->idx_arr [heap->arr [dad].idx] = dad;

        dad = child;
    }

    heap->arr [dad] = dad_node;
    heap->idx_arr [dad_node.idx] = dad;

    sift_up (heap, dad);
}

size_t get_left_child (size_t dad)
{
    return dad * 2 + 1;
}

size_t get_right_child (size_t dad)
{
    return dad * 2 + 2;
}

void swap (Heap *heap, size_t i, size_t j)
{
    if (!heap) return;
    bin_node swap_val = heap->arr [i];
    heap->arr [i] = heap->arr [j];
    heap->arr [j] =  swap_val;

    heap->idx_arr [heap->arr[i].idx] = i;
    heap->idx_arr [heap->arr[j].idx] = j;
}

void new_lower_key (Heap *heap, int idx, void *new_val)
{
    if (!heap || !new_val) return;
    unsigned pos = heap->idx_arr [idx];
    
    heap->arr [pos].val = new_val;
    
    sift_up (heap, pos);
    
    return;
}

bin_node extract_min (Heap *heap)   
{
    bin_node chtoto = {};
    if (!heap || !heap->arr) return chtoto;
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

void dijkstra (graph_t *graph, int start_node, unsigned *shortest_distances, Heap *heap)
{
    if (!heap || !graph || !shortest_distances) return;
    for (int i = 0; i < graph->nodes_count; i++)
    {
        shortest_distances [i] = UINT_MAX;
        heap->idx_arr [i] = NOT_IN_HEAP;
    }

    shortest_distances [start_node] = 0;
    insert (heap, shortest_distances + start_node, start_node);

    while (heap->size > 0)
    {
        bin_node min_node = extract_min (heap);
        int v = min_node.idx;
        heap->idx_arr [v] = VISITED;

        edge_t *edge = graph->nodes_arr [v];
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
                    insert (heap, shortest_distances + idx, idx);
                }
                else
                {
                    new_lower_key (heap, idx, shortest_distances + idx);
                }
            }
            edge = edge->next;
        }
    }
}
