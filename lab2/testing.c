#include "testing.h"

double *test_sort_func (const char *test_dir, sort_func_ptr sort_func, unsigned size, unsigned step)
{
    char cur_path [128] = {};

    FILE *test_file_in  = NULL;
    FILE *test_file_out = NULL;
    
    
    double *time_arr = (double *) calloc (size / step, sizeof (double));

    int size_idx = -1;
    int flag = 1;

    for (unsigned cur_size = 0; cur_size <= size; cur_size += step)
    {
        size_idx++;
        double five_tests_time = 0;

        printf ("\rProcessing: size %u ", cur_size);
        fflush (stdout);

        for (int i = 0; i < 5; i++)
        {
            sprintf (cur_path, "%s%u_%d.in", test_dir, cur_size, i);

            test_file_in = fopen (cur_path, "r");
            unsigned *arr = (unsigned *) calloc (cur_size, sizeof (unsigned));

            for (int idx_string = 0; idx_string < cur_size; idx_string++)
            {
                fscanf (test_file_in, "%u", arr + idx_string);
            }

            five_tests_time -= get_mikro_time ();
            
            sort_func (arr, cur_size);

            five_tests_time += get_mikro_time ();

            sprintf (cur_path, "%s%u_%d.out", test_dir, cur_size, i);
            test_file_out = fopen (cur_path, "r");
            
            flag = check_sort (arr, test_file_out, cur_size);

            free (arr);
            fclose (test_file_in);
            fclose (test_file_out);

            assert (flag);
        }

        five_tests_time /= 5;
        time_arr [size_idx] = five_tests_time;
    }
    return time_arr;
}

int check_sort (unsigned *sorted_arr, FILE *test_file_out, unsigned size)
{
    unsigned val = 0;
    for (unsigned i = 0; i < size; i++)
    {
        fscanf (test_file_out, "%u", &val);
        if (val != sorted_arr [i])
        {
            return 0;
        }
    }
    return 1;
}

double get_mikro_time () 
{
    struct timeval tv;

    gettimeofday (&tv, NULL);

    return (double) tv.tv_sec + (double) tv.tv_usec / 1e6;
}