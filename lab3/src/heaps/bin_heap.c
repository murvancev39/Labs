#include "bin_heap.h"

unsigned *build_linear (unsigned *arr, size_t size)
{
    Heap heap = {};

    heap.arr = arr;
    heap.capacity = size;
    heap.size = size;
    int cur_idx = (size / 2) - 1;

    for (; cur_idx >= 0; cur_idx--)
    {
        bottom_up_sift_down (&heap, cur_idx);
    }

    return heap.arr;
}

unsigned *build_insertion (unsigned *arr, size_t size)
{
    Heap heap = {};

    heap.arr = arr;
    heap.capacity = size;
    heap.size = size;

    for (size_t i = 0; i < size; i++)
    {
        sift_up (&heap, i);
    }

    return heap.arr;
}


void insert (Heap *heap, unsigned x)
{
    if (heap->size >= heap->capacity)
    {
        heap->capacity *= 2;
        heap->arr = (unsigned *) realloc (heap->arr, heap->capacity * sizeof (unsigned));
    }
    heap->arr [heap->size] = x;
    sift_up (heap, heap->size);
    heap->size++;
    
    return ;
}

void sift_up (Heap* heap, size_t idx)
{
    unsigned cur_val = heap->arr [idx];
    size_t dad = 0;
    unsigned dad_val = 0;

    while (idx != 0)
    {
        dad = (idx - 1) / 2;
        dad_val = heap->arr [dad];

        if (dad_val > cur_val)
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
    if (idx >= heap->size)
    {
        return;
    }

    size_t left = idx * 2 + 1;
    size_t right = idx * 2 + 2;
    size_t dad = idx;
    unsigned dad_val = heap->arr [dad];
    unsigned left_val = 0;
    unsigned right_val = 0;


    while (right < heap->size)
    {    
        left_val = heap->arr [left];
        right_val = heap->arr [right];
        if (left_val < right_val)
        {
            heap->arr [dad] = left_val;
            dad = left;
        }
        else
        {
            heap->arr [dad] = right_val;
            dad = right;
        }
        left = dad * 2 + 1;
        right = dad * 2 + 2;
    }

    if (left < heap->size)
    {
        heap->arr [dad] = heap->arr [left];
        dad = left;
    }

    heap->arr [dad] = dad_val;

    sift_up (heap, dad);
    return;
}


void swap (Heap *heap, size_t i, size_t j)
{
    unsigned swap_val = heap->arr [i];
    heap->arr [i] = heap->arr [j];
    heap->arr [j] =  swap_val;
}
