#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdio.h>
#include <stdlib.h>

void merge (unsigned *arr, unsigned *buffer, size_t left, size_t mid, size_t right);
void merge_sort_recursive_internal (unsigned *arr, unsigned *buffer, size_t left, size_t right);
void merge_sort_recursive (unsigned *arr, size_t n);
void merge_sort_iterative (unsigned *arr, size_t n);


#endif