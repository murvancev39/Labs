#include "tester.h"


int write_test_result (const char *func_name, double *time_arr, const char *result_dir, unsigned size, unsigned step)
{
    if (!func_name) return 1;    
    if (!time_arr) return 1;    
    if (!result_dir) return 1;
    
    char result_path [64] = {0};
    snprintf (result_path, MAX_PATH_LEN, "%s_%s_sort.txt", result_dir, func_name);
    
    FILE *res_file = fopen (result_path, "w");
    if (!res_file) return 1;
    
    unsigned ind = 0;
    // printf ("\n\n%s\n\n", result_path);
    for (unsigned i = step; i <= size; i += step) 
    {
        // printf ("%u %lf\n", i, time_arr [i / step]);
        fprintf (res_file, "%u %lf\n", i, time_arr [ind]);
        ind++;
    }
    
    fclose (res_file);
    return 0;
}

int run_tests  (const char *test_dir, const char *func_name, sort_func_ptr_t sort_func, 
                            const char *result_dir, unsigned size, unsigned step)
{
    if (!test_dir) return 1;    
    if (!func_name) return 1;
    if (!sort_func) return 1;
    if (!result_dir) return 1;
    
    
    double *time_arr = test_sort_func (test_dir, sort_func, size, step);
    
    if (!time_arr) return 1;
    // printf ("\n\nDOLBOEB\n\n");
    
    if (!write_test_result (func_name, time_arr, result_dir, size, step)) return 1;
    
    free (time_arr);
    return 0;
}