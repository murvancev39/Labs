#ifndef ALL_PARTS_H
#define ALL_PARTS_H

#include "tester.h"
#include "quadratic_sorts.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "quick_sorts_partition.h"
#include "quick_sorts_pivot.h"
#include <string.h>


#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 50000

typedef struct inter
{
    char path_tests_from [128];
    const char func_name [32];
    sort_func_ptr_t sort_f;
    char path_tests_to [128];
    const unsigned test_size;
    const unsigned test_step;
} test_interface;

int run_part_1 (char res_dir_path [], char tests_dir_path []);
int run_part_2 (char res_dir_path [], char tests_dir_path []);
int run_part_3 (char res_dir_path [], char tests_dir_path []);
int run_part_4 (char res_dir_path [], char tests_dir_path []);
int run_part_5 (char res_dir_path [], char tests_dir_path []);
int run_part_10 (char res_dir_path [], char tests_dir_path []);
int int_compare (const void *a, const void *b);
void std_qsort (unsigned *arr, size_t size);


#endif