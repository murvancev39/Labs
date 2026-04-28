#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <string.h>

#define MAX_PATH_LEN 128
#define PATH_LEN_OWERFLOW_PTR ((void *) 2)
#define PATH_LEN_OWERFLOW_INT 2
typedef int (*sort_func_ptr_t) (unsigned *, size_t);

double *test_sort_func (const char *test_dir, sort_func_ptr_t sort_func, unsigned size, unsigned step);
int check_sort (unsigned *sorted_arr, FILE *test_file_out, unsigned size);
double get_mikro_time ();

#endif