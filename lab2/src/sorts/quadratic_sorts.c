#include "quadratic_sorts.h"

int insertion_sort (unsigned* arr, size_t size)
{
    if (size < 2) return 0;
    if (!arr) return 0;

    for (size_t cur = 1; cur < size; cur++) 
    {
        unsigned key = arr [cur];

        int left = cur - 1;
        
        while (left >= 0 && arr [left] > key) 
        {
            arr [left + 1] = arr [left];
            left--;
        }
        arr [left + 1] = key;
    }
    return 0;
}

int bubble_sort (unsigned* arr, size_t size) 
{
    if (size < 2) return 0;
    if (!arr) return 0;

    for (size_t i = 0; i < size - 1; i++) 
    {
        unsigned swapped = 0;

        for (size_t j = 0; j < size - i - 1; j++) 
        {
            if (arr [j] > arr [j + 1]) 
            {
                unsigned temp = arr [j];
                arr [j] = arr [j + 1];
                arr [j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) 
        {
            break;
        }
    }
    return 0;
}


int selection_sort (unsigned* arr, size_t size) 
{
    if (size < 2) return 0;
    if (!arr) return 0;

    for (size_t i = 0; i < size - 1; i++) 
    {
        size_t min_idx = i;

        for (size_t j = i + 1; j < size; j++) 
        {
            if (arr [j] < arr [min_idx]) 
            {
                min_idx = j;
            }
        }

        if (min_idx != i) 
        {
            unsigned temp = arr [i];
            arr [i] = arr [min_idx];
            arr [min_idx] = temp;
        }
    }
    return 0;
}

int shell_sort (unsigned *arr, size_t size) 
{
    if (size < 2) return 0;
    if (!arr) return 0;

    size_t h = 1;
    while (h < size / 3) 
    {
        h = 3 * h + 1;
    }

    while (h >= 1) 
    {
        for (size_t cur = h; cur < size; cur++) 
        {
            unsigned key = arr[cur];
            int left = (int) cur - (int) h;

            while (left >= 0 && arr [left] > key) 
            {
                arr [left + h] = arr [left];
                left -= (int) h;
            }
            arr [left + h] = key;
        }
        
        h /= 3;
    }
    return 0;
}