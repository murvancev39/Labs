#include "quick_sorts_pivot.h"
// int main ()
// {
//     unsigned arr [10] = {1,4,64,6,4,2,4,6,9,7};

//     quick_sort_hoar_med_3_rand (arr, 10);

//     for (int i = 0; i < 10; i++)
//     {
//         printf ("%u\n", arr [i]);
//     }
//     return 0;
// }


void quick_sort_hoar_med_3_rand (unsigned *arr, size_t size)
{
    while (size > 1) 
    {
        size_t p = partition_hoar_med_3_rand (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_hoar_med_3_rand (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}

size_t partition_hoar_med_3_rand (unsigned *arr, size_t size)
{
    unsigned pivo = get_median_of_three_random (arr, size);
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


void quick_sort_hoar_rand (unsigned *arr, size_t size) 
{
    while (size > 1) 
    {
        size_t p = partition_hoar_random (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_hoar_rand (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}

size_t partition_hoar_random (unsigned *arr, size_t size)
{
    unsigned pivo = get_random_pivo (arr, size);
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

unsigned get_random_pivo (unsigned *arr, size_t size)
{
    unsigned idx = 0;
    
    if (size < RAND_MAX)
    {
        idx = get_rand_below (size);
        return arr [idx];
    }

    unsigned k = size / RAND_MAX;
    idx = rand () * k;

    return arr [idx];
}

unsigned get_rand_below (unsigned max_val)
{
    if (max_val == 0)
    {
        return 0;
    }
    unsigned val = rand ();
    unsigned range = (RAND_MAX / max_val) * max_val;
    while (val >= range)
    {
        val = rand ();
    }
    return val % max_val;
}


size_t get_median_of_three_random (unsigned* arr, size_t size)
{
    if (size < 2) 
    {
        return 0;
    }

    size_t idx1 = rand () % size;
    size_t idx2 = rand () % size;
    size_t idx3 = rand () % size;

    unsigned val1 = arr [idx1];
    unsigned val2 = arr [idx2];
    unsigned val3 = arr [idx3];

    if ((val1 <= val2 && val2 <= val3) || (val3 <= val2 && val2 <= val1)) 
    {
        return val2;
    }
    
    if ((val2 <= val1 && val1 <= val3) || (val3 <= val1 && val1 <= val2)) 
    {
        return val1;
    }

    return val3;
}

void quick_sort_hoar_med_of_med (unsigned *arr, size_t size)
{
    while (size > 1) 
    {
        size_t p = partition_hoar_med_of_med (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_hoar_med_of_med (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}

size_t partition_hoar_med_of_med (unsigned *arr, size_t size)
{
    unsigned pivo = get_median_of_medians (arr, size);
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


void insertion_sort_for_median (unsigned* arr, size_t size)
{
    for (size_t cur = 1; cur < size; cur++) 
    {
        unsigned key = arr [cur];
        int left = (int) cur - 1;
        while (left >= 0 && arr [left] > key) 
        {
            arr [left + 1] = arr [left];
            left--;
        }
        arr [left + 1] = key;
    }
}

unsigned get_median_of_medians (unsigned* arr, size_t size)
{
    if (size <= 5) 
    {
        insertion_sort_for_median (arr, size);
        return arr [size / 2];
    }

    size_t num_groups = (size + 4) / 5;
    for (size_t i = 0; i < num_groups; i++) 
    {
        size_t group_start = i * 5;
        size_t group_size = (group_start + 5 <= size) ? 5 : (size - group_start);
        
        insertion_sort_for_median (arr + group_start, group_size);
        
        unsigned temp = arr [i];
        arr [i] = arr [group_start + group_size / 2];
        arr [group_start + group_size / 2] = temp;
    }

    return get_median_of_medians (arr, num_groups);
}


unsigned get_median_of_three (unsigned *arr, size_t size)
{
    if (size == 0)
    {
        return 0;
    }

    if (size == 1)
    {
        return arr [0];
    }

    size_t first = 0;
    size_t mid = size / 2;
    size_t last = size - 1;

    unsigned v1 = arr [first];
    unsigned v2 = arr [mid];
    unsigned v3 = arr [last];

    if ((v1 <= v2 && v2 <= v3) || (v3 <= v2 && v2 <= v1))
    {
        return v2;
    }

    if ((v2 <= v1 && v1 <= v3) || (v3 <= v1 && v1 <= v2))
    {
        return v1;
    }

    return v3;
}

size_t partition_hoar_med_of_three (unsigned *arr, size_t size)
{
    unsigned pivo = get_median_of_three (arr, size);
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


void quick_sort_hoar_med_of_three (unsigned *arr, size_t size)
{
    while (size > 1) 
    {
        size_t p = partition_hoar_med_of_three (arr, size);

        if (p == size - 1)
        {
            size--;
            continue;
        }

        quick_sort_hoar_med_of_three (arr, p + 1);

        arr += (p + 1);
        size -= (p + 1);
    }
}

