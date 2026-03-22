#ifndef QUICK_SORTS_PARTITION
#define QUICK_SORTS_PARTITION

#include <stdio.h>
#include <stdlib.h>

struct index
{
    size_t left;
    size_t right;
};

typedef struct index Index;

void quick_sort_hoar (unsigned *begin, size_t size);
size_t partition_hoar (unsigned *arr, size_t size);
size_t partition_lomuto (unsigned *arr, size_t size);
void quick_sort_lomuto (unsigned *arr, size_t size);
Index partition_fat (unsigned *arr, size_t size);
void quick_sort_fat (unsigned *arr, size_t size);


#endif