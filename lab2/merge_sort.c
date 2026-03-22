#include "merge_sort.h"

void merge (unsigned *arr, unsigned *buffer, size_t left, size_t mid, size_t right)
{
    size_t it1 = 0;
    size_t it2 = 0;
    
    while (left + it1 < mid && mid + it2 < right) 
    {
        if (arr [left + it1] <= arr [mid + it2]) 
        {
            buffer [left + it1 + it2] = arr [left + it1];
            it1++;
        } 
        else 
        {
            buffer [left + it1 + it2] = arr [mid + it2];
            it2++;
        }
    }

    while (left + it1 < mid) 
    {
        buffer [left + it1 + it2] = arr [left + it1];
        it1++;
    }

    while (mid + it2 < right) 
    {
        buffer [left + it1 + it2] = arr [mid + it2];
        it2++;
    }

    for (size_t i = left; i < right; i++) 
    {
        arr [i] = buffer [i];
    }
    return;
}


void merge_sort_recursive_internal (unsigned *arr, unsigned *buffer, size_t left, size_t right)
{
    if (right - left <= 1) 
    {
        return;
    }

    size_t mid = left + (right - left) / 2;

    merge_sort_recursive_internal (arr, buffer, left, mid);
    merge_sort_recursive_internal (arr, buffer, mid, right);

    merge (arr, buffer, left, mid, right);
}

void merge_sort_recursive (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }
    unsigned *buffer = (unsigned *) malloc (n * sizeof (unsigned));
    merge_sort_recursive_internal (arr, buffer, 0, n);
    free (buffer);
}

void merge_sort_iterative (unsigned *arr, size_t n)
{
    if (n < 2) 
    {
        return;
    }

    unsigned *buffer = (unsigned *) malloc (n * sizeof (unsigned));

    for (size_t size = 1; size < n; size *= 2) 
    {
        for (size_t left = 0; left < n - size; left += 2 * size) 
        {
            size_t mid = left + size;
            size_t right = left + 2 * size;
            if (right > n) 
            {
                right = n;
            }
            merge (arr, buffer, left, mid, right);
        }
    }

    free (buffer);
}


