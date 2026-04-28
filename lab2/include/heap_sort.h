#ifndef HEAP_SORT_H
#define HEAP_SORT_H

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
int heap_sort_bottom_up (unsigned *arr, size_t n, size_t k);
int heap_sort_bottom_up_2 (unsigned *arr, size_t n);
int heap_sort_bottom_up_3 (unsigned *arr, size_t n);
int heap_sort_bottom_up_4 (unsigned *arr, size_t n);
int heap_sort_bottom_up_5 (unsigned *arr, size_t n);
int heap_sort_bottom_up_6 (unsigned *arr, size_t n);
int heap_sort_bottom_up_7 (unsigned *arr, size_t n);
int heap_sort_bottom_up_8 (unsigned *arr, size_t n);
int heap_sort_bottom_up_9 (unsigned *arr, size_t n);
int heap_sort_bottom_up_10 (unsigned *arr, size_t n);

#endif