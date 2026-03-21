#include "tester.h"


void write_test_result (const char *func_name, double *time_arr, const char *result_dir, int num_elem)
{
    char result_path [64] = {0};
    sprintf (result_path, "%s%s_sort", result_dir, func_name);
    FILE *res_file = fopen (result_path, "w");

    for (int i = 0; i < num_elem; i++) 
    {
        fprintf (res_file, "%lf\n", time_arr [i]);
    }

    fclose (res_file);
    return;
}

void run_tests  (const char *test_dir, const char *func_name, sort_func_ptr sort_func, 
                            const char *result_dir, unsigned size, unsigned step)
{
    double *time_arr = test_sort_func (test_dir, sort_func, size, step);
    
    write_test_result (func_name, time_arr, result_dir, size / step);
    
    free (time_arr);
    return;
}