#ifndef TESTING_H

#define TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>

typedef void (* sort_func_ptr ) (unsigned *, size_t);

double *test_sort_func (const char *test_dir, sort_func_ptr sort_func, unsigned size, unsigned step);
int check_sort (unsigned *sorted_arr, FILE *test_file_out, unsigned size);
double get_mikro_time ();

#endif