#ifndef TESTER_H
#define TESTER_H

#include "testing.h"

void write_test_result (const char *func_name, double *time_arr, const char *result_dir, int num_elem);
void run_tests (const char *test_dir, const char *func_name, sort_func_ptr sort_func, 
                const char *result_dir, unsigned size, unsigned step);

#endif