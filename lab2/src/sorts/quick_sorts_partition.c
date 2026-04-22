#include "quick_sorts_partition.h"

size_t partition_hoar (unsigned *arr, size_t size) 
{
    unsigned pivo = arr [size / 2];
    size_t i = 0;
    size_t j = size - 1;

    while (1) 
    {
        while (arr [i] < pivo) 
        {
            i++;
        }
        
        while (arr [j] > pivo) 
        {
            j--;
        }

        if (i >= j) 
        {
            return j;
        }

        unsigned temp = arr [i];
        arr [i] = arr [j];
        arr [j] = temp;

        i++;
        j--;
    }
}

size_t partition_lomuto (unsigned *arr, size_t size)
{
    unsigned pivo = arr [size / 2];
    
    unsigned temp_p = arr [size / 2];
    arr [size / 2] = arr [size - 1];
    arr [size - 1] = temp_p;

    size_t i = 0;
    for (size_t j = 0; j < size - 1; j++) 
    {
        if (arr [j] <= pivo) 
        {
            unsigned temp = arr [i];
            arr [i] = arr [j];
            arr [j] = temp;
            i++;
        }
    }

    unsigned temp_final = arr [i];
    arr [i] = arr [size - 1];
    arr [size - 1] = temp_final;

    return i;
}

void quick_sort_hoar (unsigned *arr, size_t size) 
{
    while (size > 1) 
    {
        size_t p = partition_hoar (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_hoar (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}

void quick_sort_lomuto (unsigned *arr, size_t size) 
{
    while (size > 1) 
    {
        size_t p = partition_lomuto (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_lomuto (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}




Index partition_fat (unsigned *arr, size_t size)
{
    unsigned pivo = arr [size / 2];
    size_t lt = 0;
    size_t i = 0;
    size_t gt = size - 1;

    while (i <= gt) 
    {
        if (arr [i] < pivo) 
        {
            unsigned temp = arr [lt];
            arr [lt] = arr [i];
            arr [i] = temp;
            lt++;
            i++;
        } 
        else if (arr [i] > pivo) 
        {
            unsigned temp = arr [gt];
            arr [gt] = arr [i];
            arr [i] = temp;

            if (gt == 0) 
            {
                break; 
            }
            gt--;
        } 
        else 
        {
            i++;
        }
    }

    Index res = {lt, gt};
    return res;
}

void quick_sort_fat (unsigned *arr, size_t size)
{
    while (size > 1) 
    {
        Index p = partition_fat (arr, size);

        if (p.left > 1) 
        {
            quick_sort_fat (arr, p.left);
        }

        size_t right_part_start = p.right + 1;
        if (right_part_start >= size) 
        {
            break;
        }
        
        arr += right_part_start;
        size -= right_part_start;
    }
}