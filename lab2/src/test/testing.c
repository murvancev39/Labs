#include "testing.h"

double *test_sort_func (const char *test_dir, sort_func_ptr_t sort_func, unsigned size, unsigned step)
{
    if (step == 0) return NULL;
    if (!sort_func) return NULL;

    if (strlen (test_dir) > (MAX_PATH_LEN - 16))
    {
        return PATH_LEN_OWERFLOW_PTR;
    }
    
    char cur_path [MAX_PATH_LEN] = {};

    FILE *test_file_in  = NULL;
    FILE *test_file_out = NULL;
    
    double *time_arr = (double *) calloc (size / step, sizeof (double));
    if (!time_arr) return NULL;
    
    int size_idx = -1;
    int flag = 1;
    
    for (unsigned cur_size = step; cur_size <= size; cur_size += step)
    {
        size_idx++;
        double five_tests_time = 0;
        
        printf ("\rProcessing: size %u ", cur_size);
        fflush (stdout);
        
        for (unsigned i = 0; i < 5; i++)
        {
            sprintf (cur_path, "%s%u_%d.in", test_dir, cur_size, i);

            test_file_in = fopen (cur_path, "r");
            if (!test_file_in) 
            {
                free (time_arr);
                return NULL;
            }
            
            unsigned *arr = (unsigned *) calloc (cur_size, sizeof (unsigned));

            if (!arr)
            {
                fclose (test_file_in);
                free (time_arr);
                return NULL;
            }
            
            for (unsigned idx_string = 0; idx_string < cur_size; idx_string++)
            {
                if (fscanf (test_file_in, "%u", arr + idx_string) != 1)
                {
                    free (arr);
                    free (time_arr);
                    fclose (test_file_in);
                    return NULL;
                }
            }
            
            five_tests_time -= get_mikro_time ();
            
            sort_func (arr, cur_size);
            
            five_tests_time += get_mikro_time ();
            
            sprintf (cur_path, "%s%u_%d.out", test_dir, cur_size, i); 
// на всякий, тут переполнения не будет т.к проверка была до этого
            
            test_file_out = fopen (cur_path, "r");
            if (!test_file_out) 
            {
                free (arr);
                free (time_arr);
                fclose (test_file_in);
                return NULL;
            }
            flag = check_sort (arr, test_file_out, cur_size);
            
            free (arr);
            fclose (test_file_in);
            fclose (test_file_out);
            
            if (flag) 
            {
                free (time_arr);
                assert (!flag);
            }
        }

        five_tests_time /= 5;
        time_arr [size_idx] = five_tests_time;
    }
    
    return time_arr;
}

int check_sort (unsigned *sorted_arr, FILE *test_file_out, unsigned size)
{
    if (!sorted_arr) return 1;
    if (!test_file_out) return 1;

    unsigned val = 0;
    for (unsigned i = 0; i < size; i++)
    {
        if (fscanf (test_file_out, "%u", &val) != 1)
        {
            return 1;
        }
        
        if (val != sorted_arr [i])
        {
            return 1;
        }
    }
    return 0;
}

double get_mikro_time () 
{
    struct timeval tv;

    gettimeofday (&tv, NULL);

    return (double) tv.tv_sec + (double) tv.tv_usec / 1e6;
}