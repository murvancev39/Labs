#ifndef TESTER_H
#define TESTER_H

#define MAX_PATH_LEN 64

#include "testing.h"

int write_test_result (const char *func_name, double *time_arr, const char *result_dir, unsigned size, unsigned step);
int run_tests (const char *test_dir, const char *func_name, sort_func_ptr_t sort_func, 
                const char *result_dir, unsigned size, unsigned step);

#endif