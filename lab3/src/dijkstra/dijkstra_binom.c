#include "binom_dijkstra.h"

binom_heap **idx_arr_init (size_t size)
{
    binom_heap **idx_arr = (binom_heap **) malloc (size * sizeof (*idx_arr));
    for (size_t i = 0; i < size; i++)
    {
        idx_arr [i] = NOT_IN_HEAP;
    }
    return idx_arr;
}

unsigned get_min (binom_heap *heap)
{
    if (heap == NULL || heap->child == NULL)
    {
        return -1488;
    }

    binom_heap *cur = heap->child;
    binom_heap *min_node = cur;

    while (cur != NULL)
    {
        if (cur->key < min_node->key || (cur->key == min_node->key && cur->ins_idx < min_node->ins_idx))
        {
            min_node = cur;
        }
        cur = cur->bro;
    }

    return min_node->key;
}

void destroy_node (binom_heap *node)
{
    if (node == NULL) return;

    destroy_node (node->child);

    destroy_node (node->bro);

    free (node);
    return;
}

void destroy_heap (binom_heap *heap)
{
    if (heap == NULL) return;

    destroy_node(heap->child);
    heap->child = NULL;
    return;
}


binom_heap* merge_lists (binom_heap *l1, binom_heap *l2)
{
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    binom_heap *head = NULL;
    binom_heap *tail = NULL;

    // Выбираем, кто первыйй
    if (l1->degree <= l2->degree)
    {
        head = l1;
        l1 = l1->bro;
    }
    else
    {
        head = l2;
        l2 = l2->bro;
    }
    tail = head;

    while (l1 != NULL && l2 != NULL)
    {
        if (l1->degree <= l2->degree)
        {
            tail->bro = l1;
            l1 = l1->bro;
        }
        else
        {
            tail->bro = l2;
            l2 = l2->bro;
        }
        tail = tail->bro;
    }

    if (l1 != NULL) 
    {
        tail->bro = l1;
    }
    else 
    {
        tail->bro = l2;
    }

    return head;
}

void insert (binom_heap *heap, int val, int idx, binom_heap **idx_arr)
{
    binom_heap *node = (binom_heap *) calloc (1, sizeof (binom_heap));
    node->key = val;
    node->bro = heap->child;
    node->degree = 0;
    heap->child = node;
    idx_arr [idx] = node;
    node->ins_idx = idx;
    merge (heap);
    return;
}

void merge (binom_heap *heap)
{
    if (heap->child == NULL) return;

    binom_heap *prev = NULL;
    binom_heap *cur = heap->child;
    binom_heap *next = cur->bro;
    
    while (next != NULL)
    {    
        if (cur->degree != next->degree || (next->bro != NULL && next->bro->degree == cur->degree))
        {
            prev = cur;
            cur = next;
        }
        else if (cur->key < next->key)
        {// cur остается крнем, next уходит под него
            cur->bro = next->bro;
            link_tree (next, cur);
        }
        else
        {// next становится корнем, cur уходит под него
            if (prev == NULL)
            {
                heap->child = next;
            }
            else
            {
                prev->bro = next;
            }    
            link_tree (cur, next);
            cur = next;
        }
        next = cur->bro;
    }
}

void link_tree (binom_heap *from, binom_heap *where)
{
    from->parent = where;
    from->bro = where->child;
    where->child = from;
    where->degree++;
    return;
}

int extract_min(binom_heap *heap)
{
    if (heap->child == NULL) 
    {
    return -1;
    }

    binom_heap *min_node = heap->child;
    binom_heap *prev_min = NULL;
    
    binom_heap *cur = heap->child;
    binom_heap *prev = NULL;
    
    while (cur != NULL) 
    {
        if (cur->key < min_node->key || (cur->key == min_node->key && cur->ins_idx < min_node->ins_idx)) 
        {
            min_node = cur;
            prev_min = prev;
        }
        prev = cur;
        cur = cur->bro;
    }
    if (prev_min == NULL) 
    {
        heap->child = min_node->bro;
    }
    else 
    {
        prev_min->bro = min_node->bro;
    }

    binom_heap *child_list = reverse_list(min_node->child);

    heap->child = merge_lists(heap->child, child_list);

    merge(heap);
    int ins_idx = min_node->ins_idx;
    free (min_node);
    return ins_idx;
}


binom_heap* reverse_list (binom_heap *root)
{
    binom_heap *prev = NULL;
    binom_heap *curr = root;
    binom_heap *next = NULL;

    while (curr != NULL)
    {
        next = curr->bro;
        curr->bro = prev;
        curr->parent = NULL;
        
        prev = curr;
        curr = next;
    }

    return prev;
}

void sift_up (binom_heap *node, binom_heap **idx_arr)
{
    while (node->parent != NULL && (node->key < node->parent->key || 
          (node->key == node->parent->key && node->ins_idx < node->parent->ins_idx)))
    {
        int temp_key = node->key;
        int temp_idx = node->ins_idx;
        
        node->key = node->parent->key;
        node->ins_idx = node->parent->ins_idx;
        
        node->parent->key = temp_key;
        node->parent->ins_idx = temp_idx;

        idx_arr[node->ins_idx] = node;
        idx_arr[node->parent->ins_idx] = node->parent;

        node = node->parent;
    }
}

void delete_node (binom_heap *node, binom_heap *heap, binom_heap **idx_arr)
{
    if (node == NULL) 
    {
        return;
    }
    node->key = -2147483648;
    sift_up(node, idx_arr);
    extract_min(heap);
}

void update_key (binom_heap *node, unsigned new_val, binom_heap **idx_arr, binom_heap *heap)
{
    if (node == NULL)
    {
        return;
    }

    unsigned old_val = node->key;
    int current_ins_idx = node->ins_idx;

    if (new_val < old_val)
    {
        node->key = new_val;
        sift_up (node, idx_arr);
    }
    else if (new_val > old_val)
    {
        delete_node (node, heap, idx_arr);
        
        insert (heap, new_val, current_ins_idx, idx_arr);
    }
}

void dijkstra (Graph *graph, int start_node, unsigned *shortest_distances, binom_heap *heap, binom_heap **idx_arr)
{
    for (int i = 0; i < graph->nodes_count; i++)
    {
        shortest_distances [i] = UINT_MAX;
        idx_arr [i] = NOT_IN_HEAP;
        // printf ("tut");
    }

    shortest_distances [start_node] = 0;
    insert (heap, 0, start_node, idx_arr);
    // int i = 0;
    while (heap->child != NULL)
    {
        int min_node_idx =  extract_min (heap);
        // printf ("%d! %d \n", i, min_node_idx);
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
                    insert (heap, shortest_distances [idx], idx, idx_arr);
                }
                else
                {
                    update_key (idx_arr [idx], shortest_distances [idx], idx_arr, heap);
                }
            }
            edge = edge->next;
        }
    }
}
