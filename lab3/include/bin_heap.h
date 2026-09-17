#ifndef BIN_HEAPP_H 
#define BIN_HEAPP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct heap
{
    void **arr;
    size_t capacity;
    size_t size;
    int (*cmp) (void *, void *);
};

typedef struct heap Heap;

void **build_insertion (void **arr, size_t size, int (*cmp) (void *, void *));
void **build_linear (void **arr, size_t size, int (*cmp) (void *, void *));
void insert (Heap *heap, void *x);
void sift_up (Heap* heap, size_t idx);
void bottom_up_sift_down (Heap *heap, size_t idx);
void swap (Heap *heap, size_t i, size_t j);

size_t get_left_child (size_t dad);
size_t get_right_child (size_t dad);
#endif