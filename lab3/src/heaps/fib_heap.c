#include "fib_heap.h"

fib_node **idx_arr_init (size_t size)
{
    fib_node **idx_arr = (fib_node **) malloc (size * sizeof (*idx_arr));
    for (size_t i = 0; i < size; i++)
    {
        idx_arr [i] = NOT_IN_HEAP;
    }
    return idx_arr;
}


void destruct_nodes (fib_node *node)
{
    if (node == NULL)
    {
        return;
    }

    node->left_bro->right_bro = NULL;
    
    fib_node *next = NULL;
    fib_node *cur = node;

    while (cur != NULL)
    {
        next = cur->right_bro;
        destruct_nodes (cur->child);
        free (cur);
        cur = next;
    }
        
    return;
}


unsigned get_min (fib_heap *heap)
{
    return heap->min->elem;
}

void merge_lists (fib_node *node_1, fib_node *node_2)
{
    fib_node *last_node_2 = node_2->left_bro;
    fib_node *second_node_1 = node_1->right_bro;
    node_1->right_bro = node_2;
    node_2->left_bro = node_1;
    last_node_2->right_bro = second_node_1;
    second_node_1->left_bro = last_node_2;
}

void merge_heaps (fib_heap *heap_1, fib_heap *heap_2)
{
    // printf ("merge_heaps {h1 %d|h2 %d}\n", heap_1->n, heap_2->n);
    if (heap_1->min == NULL)
    {
        heap_1->min = heap_2->min;
        heap_1->n = heap_2->n;
        return;
    }
    if (heap_2->min == NULL)
    {
        return;
    }

    heap_1->n += heap_2->n;

    if (heap_1->min->elem < heap_2->min->elem)
    {
        merge_lists (heap_1->min, heap_2->min);
        return;
    }

    merge_lists (heap_2->min, heap_1->min); 
    heap_1->min = heap_2->min;
    return;
}

fib_node *link (fib_node *node_1, fib_node *node_2)
{
    if (node_1 == NULL)
    {
        return node_2;
    }
    if (node_2 == NULL)
    {
        return node_1;
    }

    if (node_1->elem < node_2->elem)
    {
        if (node_1->child != NULL)
        {            
            merge_lists (node_2, node_1->child);

            node_1->child = node_2;
            node_2->parent = node_1;
            
            node_1->son_is_dead = no;
            return node_1;
        }
        else
        {
            node_1->child = node_2;
            node_2->parent = node_1;
            
            node_1->son_is_dead = no;
            return node_1;
        }
    }
    if (node_2->child != NULL)
    {
        merge_lists (node_1, node_2->child);
        node_2->child = node_1;
        node_1->parent = node_2;
            
        node_2->son_is_dead = no;
        return node_2;
    }
    node_2->child = node_1;
    node_1->parent = node_2;

    node_2->son_is_dead = no;
    return node_2;
}

void fill_heap_by_nodes_arr (fib_heap *heap, fib_node **fib_arr, unsigned len)
{
    unsigned i = 0;
    while (fib_arr [i] == NULL)
    {
        i++;
    }

    heap->min = fib_arr [i];
    heap->min->left_bro = heap->min;
    heap->min->right_bro = heap->min;
    i++;

    fib_node *cur_node = NULL;
    for (; i < len; i++)
    {
        cur_node = fib_arr [i];
        if (cur_node != NULL)
        {
            heap->min->left_bro->right_bro = cur_node;
            cur_node->left_bro = heap->min->left_bro;
            cur_node->right_bro = heap->min;
            heap->min->left_bro = cur_node;
        }
    }
    return;
}


void consolidate (fib_heap *heap)
{
    assert (heap);
    if (heap->min == NULL)
    {
        return;
    }
    
    unsigned len = 32;
    fib_node **fib_arr = (fib_node **) calloc (len, sizeof (fib_node *));

    
    int num_roots = 0;
    fib_node *cur_node = heap->min;
    do
    {
        num_roots++;
        cur_node = cur_node->right_bro;
    } while (cur_node != heap->min);
    
    fib_node *right_bro = heap->min->right_bro;
    fib_node *arr_node = NULL;
    int degree = 0;

    fib_node *min_node = cur_node;

    for (int i = 0; i < num_roots; i++)
    {
        degree = cur_node->degree;
        arr_node = fib_arr [degree];

        cur_node->left_bro = cur_node;
        cur_node->right_bro = cur_node;

        while (arr_node != NULL)
        {            
            arr_node->left_bro = arr_node;
            arr_node->right_bro = arr_node;

            cur_node = link (arr_node, cur_node);

            fib_arr [degree] = NULL;

            cur_node->degree++;
            degree++;
            arr_node = fib_arr [degree];
            cur_node->son_is_dead = no;
        }

        fib_arr [degree] = cur_node;

        cur_node = right_bro;
        if (right_bro != NULL)
        {
            right_bro = right_bro->right_bro;
        }
    }
    fill_heap_by_nodes_arr (heap, fib_arr, len);

    cur_node = heap->min;
    min_node = cur_node;
    do
    {
        if (cur_node->elem < min_node->elem)
        {
            min_node = cur_node;
        }
        cur_node = cur_node->right_bro;
    } while (cur_node != heap->min);
    heap->min = min_node;
    
    free (fib_arr);
    return;
}

int extract_min (fib_heap *heap, fib_node **idx_arr)
{// овзвращает индекс
    if (heap->min == NULL)
    {
        return -1;
    }

    fib_heap second_heap = {};
    second_heap.min = heap->min->child;
    fib_node *node = second_heap.min;
    if (node != NULL)
    {
        do
        {
            // printf ("\n!!!");
            node->parent = NULL;
            node = node->right_bro;
        } while (node != second_heap.min);
    }
    
    
    fib_node *extract_node = heap->min;
    int idx = extract_node->dijkstra_id;
    heap->n--;

    idx_arr [idx] = VISITED;

    heap->min = extract_node->right_bro;
    heap->min->left_bro = extract_node->left_bro;
    extract_node->left_bro->right_bro = heap->min;

    extract_node->right_bro = extract_node;
    extract_node->left_bro = extract_node;
    

    if (heap->min == extract_node)
    {
        heap->min = NULL;
        second_heap.n = heap->n;
        heap->n = 0;
        merge_heaps (heap, &second_heap);
        consolidate (heap);
        free (extract_node);
        return idx;
    }
    merge_heaps (heap, &second_heap);
    consolidate (heap);
    free (extract_node);
    return idx;
}

fib_node *insert_val (fib_heap *heap, unsigned val, int dijkstra_id)
{
    assert (heap);

    fib_heap second_heap = {};
    fib_node *node = (fib_node *) calloc (1, sizeof (fib_node));
    node->child = NULL;
    node->degree = 0;
    node->elem = val;
    node->left_bro = node;
    node->right_bro = node;
    node->parent = NULL;
    node->son_is_dead = no;
    node->dijkstra_id = dijkstra_id;

    second_heap.min = node;
    second_heap.n = 1;

    merge_heaps (heap, &second_heap);

    return node;
}

void insert_node (fib_heap *heap, fib_node *new_node)
{
    assert (heap);
    assert (new_node);
    new_node->son_is_dead = no;
    new_node->parent = NULL;
    
    if (heap->min == NULL)
    {
        heap->min = new_node;
        return;
    }

    heap->min->left_bro->right_bro = new_node;
    new_node->left_bro = heap->min->left_bro;
    new_node->right_bro = heap->min;
    heap->min->left_bro = new_node;
    
    if (new_node->elem < heap->min->elem)
    {
        heap->min = new_node;
    }
    return;
}

void new_lower_key (fib_heap *heap, fib_node *node, unsigned val)
{
    fib_node *parent = node->parent;
    node->elem = val;
    if (parent == NULL)
    {
        if (node->elem < heap->min->elem)
        {
            heap->min = node;
        }
        return;
    }

    if (node->elem < parent->elem)
    {
        cut (node);
        insert_node (heap, node);
        cut_rec (heap, parent);
    }

    if (node->elem < heap->min->elem)
    {
        heap->min = node;
    }

    return;
}

void cut (fib_node *node)
{// тут parent не NULL всегда
    fib_node *parent = node->parent;
    if (parent->child == node)
    {
        parent->child = node->right_bro;
    }

    node->left_bro->right_bro = node->right_bro;
    node->right_bro->left_bro = node->left_bro;
    node->left_bro = node;
    node->right_bro = node;
    node->parent = NULL;

    if (parent->child == node)
    {
        parent->child = NULL;
    }

    parent->degree--;
    return;
}

void cut_rec (fib_heap *heap, fib_node *node)
{
    if (node == NULL)
    {
        return;
    }

    fib_node *parent = node->parent;
    if (parent == NULL)
    {
        return;
    }

    if (node->son_is_dead == yea)
    {
        cut (node);
        insert_node (heap, node);
        cut_rec (heap, parent);
        return;
    }
    node->son_is_dead = yea;
    return;
}

void dijkstra (Graph *graph, int start_node, unsigned *shortest_distances, fib_heap *heap, fib_node **idx_arr)
{
    for (int i = 0; i < graph->nodes_count; i++)
    {
        shortest_distances [i] = UINT_MAX;
        idx_arr [i] = NOT_IN_HEAP;
    }
    
    shortest_distances [start_node] = 0;
    idx_arr [start_node] = insert_val (heap, 0, start_node);
    // int i = 0;

    while (heap->min != NULL)
    {
        int min_node_idx =  extract_min (heap, idx_arr);
        // assert (min_node_idx != -1);
        // printf ("%d\n", i);
        // i++;
        idx_arr [min_node_idx] = VISITED;

        Edge *edge = graph->nodes_arr [min_node_idx];
        while (edge != NULL)
        {
            int idx = edge->idx;
            unsigned weight = edge->weight;
            if  (shortest_distances [min_node_idx] != UINT_MAX && 
                (shortest_distances [min_node_idx] + weight < shortest_distances [idx]) && 
                (idx_arr [idx] != VISITED))
            {
                shortest_distances [idx] = shortest_distances [min_node_idx] + weight;

                if (idx_arr [idx] == NOT_IN_HEAP)
                {
                    idx_arr [idx] = insert_val (heap, shortest_distances [idx], idx);
                }
                else
                {
                    new_lower_key (heap, idx_arr [idx], shortest_distances [idx]);
                }
            }
            edge = edge->next;
        }
    }
    return;
}