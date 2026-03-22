#include "heap_sort.h"

// int main ()
// {
//     unsigned arr [10] = {1,7,9,4,2,6,8,6,1,44};
//     heap_sort_bottom_up_10 (arr, 10);
//     for (int i = 0; i < 10; i++)
//     {
//         printf ("%u\n", arr [i]);
//     }
//     return 0;
// }

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
    unsigned val = heap->arr [idx];

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

        if (val >= heap->arr [largest_child]) 
        {
            break;
        }

        heap->arr [cur] = heap->arr [largest_child];
        cur = largest_child;
    }

    heap->arr [cur] = val;
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

void heap_sort_bottom_up_2 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 2); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 2);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 2); 
    }
}

void heap_sort_bottom_up_3 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 3); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 3);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 3); 
    }
}

void heap_sort_bottom_up_4 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 4); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 4);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 4); 
    }
}

void heap_sort_bottom_up_5 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 5); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 5);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 5); 
    }
}

void heap_sort_bottom_up_6 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 6); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 6);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 6); 
    }
}

void heap_sort_bottom_up_7 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 7); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 7);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 7); 
    }
}

void heap_sort_bottom_up_8 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 8); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 8);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 8); 
    }
}

void heap_sort_bottom_up_9 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 9); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 9);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 9); 
    }
}

void heap_sort_bottom_up_10 (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    Heap h = {arr, n};

    for (int i = (int) ((n - 2) / 10); i >= 0; i--) 
    {
        sift_down_bottom_up (&h, (size_t) i, 10);
    }

    for (size_t i = n - 1; i > 0; i--) 
    {
        swap (&h, 0, i); 
        h.size = i;      
        sift_down_bottom_up (&h, 0, 10); 
    }
}