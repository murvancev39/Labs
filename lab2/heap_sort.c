#include <stdio.h>
#include <stdlib.h>

struct heap 
{
    unsigned *arr;
    size_t size;
};

typedef struct heap Heap;

void swap (Heap *heap, size_t i, size_t j);
void sift_up_max (Heap *heap, size_t idx, size_t k);
void sift_down_bottom_up (Heap *heap, size_t idx, size_t k);
void heap_sort_bottom_up (unsigned *arr, size_t n, size_t k);

int main ()
{
    unsigned arr [10] = {1,2,3,4,5,4,3,2,89,5};

    heap_sort_bottom_up (arr, 10, 2);

    for (int i = 0; i < 10; i ++)
    {
        printf ("%u\n", arr [i]);
    }
    
    return 0;

}

void swap (Heap *heap, size_t i, size_t j) 
{
    unsigned temp = heap->arr [i];
    heap->arr [i] = heap->arr [j];
    heap->arr [j] = temp;
}

void sift_up_max (Heap *heap, size_t idx, size_t k) 
{
    while (idx > 0) 
    {
        size_t parent = (idx - 1) / k;
        if (heap->arr [parent] < heap->arr [idx]) 
        {
            swap (heap, parent, idx);
            idx = parent;
        } 
        else 
        {
            break;
        }
    }
}

void sift_down_bottom_up (Heap *heap, size_t idx, size_t k) 
{
    size_t cur = idx;
    size_t start_idx = idx;

    while (k * cur + 1 < heap->size) 
    {
        size_t largest_child = k * cur + 1;
        size_t last_child = k * cur + k;
        if (last_child >= heap->size) 
        {
            last_child = heap->size - 1;
        }

        for (size_t child = largest_child + 1; child <= last_child; child++) 
        {
            if (heap->arr [child] > heap->arr [largest_child]) 
            {
                largest_child = child;
            }
        }
        
        swap (heap, cur, largest_child); 
        cur = largest_child;
    }

    sift_up_max (heap, cur, k); 
}

void heap_sort_bottom_up (unsigned *arr, size_t n, size_t k) 
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / k); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, k);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, k); 
    }
}