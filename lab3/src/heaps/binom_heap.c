#include "binom_heap.h"

void *get_min (binom_heap *heap)
{
    if (heap == NULL || heap->child == NULL)
    {
        return NULL;
    }

    binom_heap *cur = heap->child;
    binom_heap *min_node = cur;

    while (cur != NULL)
    {
        if (heap->cmp (cur->key, min_node->key) < 0 || (heap->cmp (cur->key, min_node->key) == 0 && cur->ins_idx < min_node->ins_idx))
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

void destroy_heap (binom_heap *heap, binom_heap **idx_arr, int n)
{
    if (!heap || !idx_arr) return;

    destroy_node(heap->child);
    heap->child = NULL;

    if (idx_arr != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            idx_arr[i] = NULL;
        }
    }
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

void insert (binom_heap *heap, void *val, int idx, binom_heap **idx_arr)
{
    if (!heap || !idx_arr || !val) return;
    binom_heap *node = (binom_heap *) calloc (1, sizeof (binom_heap));
    if (!node) return;
    node->cmp = heap->cmp;
    node->key = val;
    node->bro = heap->child;
    node->degree = 0;
    heap->child = node;
    idx_arr [idx] = node;
    node->ins_idx = idx;
    merge (heap);
    return;
}

void merge(binom_heap *heap)
{
    if (!heap) return;
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
        else if (heap->cmp (cur->key, next->key) < 0)
        {// cur остается корнем, next уходит под него
            cur->bro = next->bro;
            link_tree(next, cur);
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
            link_tree(cur, next);
            cur = next;
        }
        next = cur->bro;
    }
}

void link_tree (binom_heap *from, binom_heap *where)
{
    if (!from || !where) return;
    from->parent = where;
    from->bro = where->child;
    where->child = from;
    where->degree++;
    return;
}

int extract_min(binom_heap *heap)
{
    if (!heap || !heap->child) return -1;

    binom_heap *min_node = heap->child;
    binom_heap *prev_min = NULL;
    
    binom_heap *cur = heap->child;
    binom_heap *prev = NULL;
    
    while (cur != NULL) 
    {
        if (heap->cmp (cur->key, min_node->key) < 0 || (heap->cmp (cur->key, min_node->key) == 0 && cur->ins_idx < min_node->ins_idx)) 
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
    if (!root) return NULL;
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
    if (!node || !idx_arr) return;
    while (node->parent != NULL && (node->cmp (node->key, node->parent->key) < 0 || 
          (node->cmp (node->key, node->parent->key) == 0 && node->ins_idx < node->parent->ins_idx)))
    {
        void *temp_key = node->key;
        int temp_idx = node->ins_idx;
        int parent_idx = node->parent->ins_idx;
        
        node->key = node->parent->key;
        node->ins_idx = parent_idx;
        
        node->parent->key = temp_key;
        node->parent->ins_idx = temp_idx;

        idx_arr[parent_idx] = node;
        idx_arr[temp_idx] = node->parent;

        node = node->parent;
    }
}

void forced_sift_up (binom_heap *node, binom_heap **idx_arr)
{
    if (!node || !idx_arr) return;

    while (node->parent != NULL)
    {
        void *temp_key = node->key;
        int temp_idx = node->ins_idx;
        int parent_idx = node->parent->ins_idx;
        
        node->key = node->parent->key;
        node->ins_idx = parent_idx;
        
        node->parent->key = temp_key;
        node->parent->ins_idx = temp_idx;

        idx_arr[parent_idx] = node;
        idx_arr[temp_idx] = node->parent;

        node = node->parent;
    }
}

void delete_node (binom_heap *node, binom_heap *heap, binom_heap **idx_arr)
{
    if (node == NULL || heap == NULL || heap->child == NULL) 
    {
        return;
    }

    int original_idx = node->ins_idx;

    forced_sift_up (node, idx_arr);

    binom_heap *cur = heap->child;
    binom_heap *prev = NULL;

    while (cur != NULL && cur != node)
    {
        prev = cur;
        cur = cur->bro;
    }

    if (cur == node)
    {
        if (prev == NULL) 
        {
            heap->child = node->bro;
        }
        else 
        {
            prev->bro = node->bro;
        }

        binom_heap *child_list = reverse_list(node->child);
        
        heap->child = merge_lists(heap->child, child_list);
        
        merge(heap);
    }

    if (idx_arr != NULL)
    {
        idx_arr [original_idx] = NULL;
    }
    
    free(node);
}

void update_key (binom_heap *node, void *new_val, binom_heap **idx_arr, binom_heap *heap)
{
    if (!node || !new_val || !idx_arr || !heap) return;

    void *old_val = node->key;
    int current_ins_idx = node->ins_idx;

    if (heap->cmp (new_val, old_val) <= 0)
    {
        node->key = new_val;
        sift_up(node, idx_arr);
    }
    else if (heap->cmp (new_val, old_val) > 0)
    {
        delete_node(node, heap, idx_arr);
        
        insert(heap, new_val, current_ins_idx, idx_arr);
    }
}