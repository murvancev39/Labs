#ifndef BIN_HEAPP_H 
#define BIN_HEAPP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct heap
{
    unsigned *arr;
    size_t capacity;
    size_t size;
};

typedef struct heap Heap;

unsigned *build_insertion (unsigned *arr, size_t size);
unsigned *build_linear (unsigned *arr, size_t size);
void insert (Heap *heap, unsigned x);
void sift_up (Heap* heap, size_t idx);
void bottom_up_sift_down (Heap *heap, size_t idx);
void swap (Heap *heap, size_t i, size_t j);

#endif