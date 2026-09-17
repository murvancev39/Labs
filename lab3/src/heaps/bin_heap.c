#include "bin_heap.h"

void **build_linear (void **arr, size_t size, int (*cmp) (void *, void *))
{
    if (!arr || !cmp) return NULL;
    Heap heap = {};

    heap.cmp = cmp;
    heap.arr = arr;
    heap.capacity = size;
    heap.size = size;
    int cur_idx = ((int) size / 2) - 1;

    for (; cur_idx >= 0; cur_idx--)
    {
        bottom_up_sift_down (&heap, (size_t) cur_idx);
    }

    return heap.arr;
}

void **build_insertion (void **arr, size_t size, int (*cmp) (void *, void *))
{
    if (!arr || !cmp) return NULL;
    Heap heap = {};

    heap.cmp = cmp;
    heap.arr = arr;
    heap.capacity = size;
    heap.size = size;

    for (size_t i = 0; i < size; i++)
    {
        sift_up (&heap, i);
    }

    return heap.arr;
}


void insert (Heap *heap, void *x)
{
    if (!heap) return;
    if (heap->size >= heap->capacity)
    {
        heap->capacity *= 2;
        void **new_arr = (void **) realloc (heap->arr, heap->capacity * sizeof (void *));
        if (!new_arr) return;
        heap->arr = new_arr;
        
    }
    heap->arr [heap->size] = x;
    sift_up (heap, heap->size);
    
    heap->size++;
    
    return ;
}

void sift_up (Heap* heap, size_t idx)
{
    if (!heap) return;
    void *cur_val = heap->arr [idx];
    size_t dad = 0;
    void *dad_val = 0;

    while (idx != 0)
    {
        dad = (idx - 1) / 2;
        dad_val = heap->arr [dad];

        if (heap->cmp(dad_val, cur_val) > 0)
        {
            heap->arr [idx] = dad_val;
            idx = dad;
        }
        else
        {
            break;
        }
    }
    heap->arr [idx] = cur_val;
    return;
}

void bottom_up_sift_down (Heap *heap, size_t idx)
{
    if (!heap) return;
    if (idx >= heap->size) return;

    size_t dad = idx;
    void *dad_val = heap->arr [dad];

    while (dad * 2 + 1 < heap->size)
    {
        size_t left = get_left_child (dad);
        size_t right = get_right_child (dad);
        size_t child = left;

        if (right < heap->size && heap->cmp (heap->arr [right], heap->arr [left]) < 0)
        {
            child = right;
        }

        heap->arr [dad] = heap->arr [child];
        dad = child;
    }

    heap->arr [dad] = dad_val;

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
    void *swap_val = heap->arr [i];
    heap->arr [i] = heap->arr [j];
    heap->arr [j] =  swap_val;
}
