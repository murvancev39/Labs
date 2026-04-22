#ifndef QUICK_SORTS_PIVOT_H
#define QUICK_SORTS_PIVOT_H

#include "quick_sorts_partition.h"


void quick_sort_hoar_med_3_rand (unsigned *arr, size_t size);
size_t partition_hoar_med_3_rand (unsigned *arr, size_t size);
void quick_sort_hoar_rand (unsigned *arr, size_t size);
size_t partition_hoar_random (unsigned *arr, size_t size);
unsigned get_random_pivo (unsigned *arr, size_t size);
unsigned get_rand_below (unsigned max_val);
size_t get_median_of_three_random(unsigned* arr, size_t size);
void quick_sort_hoar_med_of_med (unsigned *arr, size_t size);
void insertion_sort_for_median(unsigned* arr, size_t size);
unsigned get_median_of_medians (unsigned* arr, size_t size);
size_t partition_hoar_med_of_med (unsigned *arr, size_t size);
void quick_sort_hoar_med_of_three (unsigned *arr, size_t size);
size_t partition_hoar_med_of_three (unsigned *arr, size_t size);
unsigned get_median_of_three (unsigned *arr, size_t size);

#endif
