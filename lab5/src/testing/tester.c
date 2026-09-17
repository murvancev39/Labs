#include "tester.h"


error_code_t run (interface_t interface)
{
    result_t *result = (result_t *) calloc (1, sizeof (result_t));
    if (!result) return alloc_error;

    error_code_t error_code = all_okey;

    testing (interface, result);
    if (result->error_code)
    {
        ERR_PRINTF("testing err");
        error_code = result->error_code;
        free (result);
        return error_code;
    }
    else 
    {
        write_result (interface, result);
    }
    if (result->error_code) ERR_PRINTF("write_result err");
    error_code = result->error_code;
    
    if (result->delete_time) free (result->delete_time);
    if (result->add_time) free (result->add_time);
    free (result);
    return error_code;
}

void testing (interface_t interface, result_t *result)
{
    if (!result) 
    {
        ERR_PRINTF("result_t *result == NULL");
        return;
    }
    srand (time (NULL));
    add_func_t      add_f      = interface.add_f;
    delete_func_t   delete_f   = interface.delete_f;
    init_func_t     init_f     = interface.init_f;
    destruct_func_t destruct_f = interface.destruct_f;
    test_gen_func_t test_gen_f = interface.test_gen_f;

    if (!add_f || !delete_f || !init_f || !destruct_f || !test_gen_f) 
    {
        ERR_PRINTF("func_ptr_error");
        result->error_code = func_ptr_error;
        return;
    }
    
    unsigned count_times    = ((interface.to - interface.from) / interface.step) + 1;
    double *add_time_arr    = (double *) calloc (count_times, sizeof (double));
    double *delete_time_arr = (double *) calloc (count_times, sizeof (double));
    result->size        = count_times;
    result->add_time    = add_time_arr;
    result->delete_time = delete_time_arr;

    clock_t time = 0;
    clock_t all_add_time = 0;
    clock_t all_delete_time = 0;
    void *tree = NULL;
    unsigned *test_arr = NULL;

    int cur_idx = 0;
    for (unsigned size = interface.from; size <= interface.to; size += interface.step)
    {
        printf ("[SIZE] - %u\n", size);
        all_add_time = 0;
        all_delete_time = 0;

        for (int k = 0; k < ITER_COUNT; k++)
        {
            tree = init_f ();
            if (!tree) 
            {
                free_in_testing (add_time_arr, delete_time_arr, NULL, NULL, NULL);
                ERR_PRINTF("alloc_error");
                result->error_code = alloc_error;
                return;
            }
            
            test_arr = test_gen_f (size);
            if (!test_arr)
            {
                free_in_testing (add_time_arr, delete_time_arr, test_arr, tree, destruct_f);
                ERR_PRINTF("alloc_error");
                result->error_code = alloc_error;
                return;
            }
// testing
// ---------------------------------------------------------------------------------------- 
            time = feel_tree_by_arr (size, test_arr, tree, result, add_f);
            if (result->error_code)
            {
                ERR_PRINTF("feel_tree_by_arr err");
                free_in_testing (add_time_arr, delete_time_arr, test_arr, tree, destruct_f);
                return;
            }
            all_add_time += time;
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
            time = delete_from_tree_by_arr (size / 2, test_arr, tree, result, delete_f);
            if (result->error_code)
            {
                ERR_PRINTF("delete_from_tree_by_arr err");
                free_in_testing (add_time_arr, delete_time_arr, test_arr, tree, destruct_f);
                return;
            }
            all_delete_time += time;
// ----------------------------------------------------------------------------------------

            free_in_testing (NULL, NULL, test_arr, tree, destruct_f);
        }
        
        add_time_arr [cur_idx]    = (((double) all_add_time) / CLOCKS_PER_SEC ) / ITER_COUNT;
        delete_time_arr [cur_idx] = (((double) all_delete_time) / CLOCKS_PER_SEC) / ITER_COUNT;
        cur_idx++;
        printf ("\r");
    }
    return;
}

void write_result (interface_t interface, result_t result [])
{
    if (!result) 
    {
        ERR_PRINTF("result_t *result == NULL");
        return;
    }

    char *add_path = NULL;
    char *delete_path = NULL;

    if (result->add_time != NULL)
    {
        add_path = make_path (interface._path, "add.txt", result);
        if (!add_path) 
        {
            ERR_PRINTF("add_path == NULL");
            return;
        }
    }

    if (result->delete_time != NULL)
    {
        delete_path = make_path (interface._path, "delete.txt", result);
        if (!delete_path) 
        {
            if (add_path) free (add_path);
            ERR_PRINTF("delete_path == NULL");   
            return;
        }
    }

    FILE *add_file    = NULL;
    FILE *delete_file = NULL;
    if (add_path)     add_file    = fopen (add_path, "w");
    if (delete_path)  delete_file = fopen (delete_path, "w");

    if (add_file)
    {
        result->error_code = output_double_arr (add_file, result->add_time, result->size);
        if (result->error_code) 
        {
            ERR_PRINTF("output_double_arr err");
            free_fclose_for_write_result (add_file, delete_file, add_path, delete_path);
            return;
        }
    }
    else
    {
        ERR_PRINTF("fopen_error");
        result->error_code = fopen_error;
        free_fclose_for_write_result (add_file, delete_file, add_path, delete_path);
        return;
    }

    if (delete_file)
    {
        result->error_code = output_double_arr (delete_file, result->delete_time, result->size);
        if (result->error_code) 
        {
            ERR_PRINTF("output_double_arr err");
            free_fclose_for_write_result (add_file, delete_file, add_path, delete_path);
            return;
        }
    }
    else
    {
        free_fclose_for_write_result (add_file, delete_file, add_path, delete_path);
        ERR_PRINTF("fopen_error");
        result->error_code = fopen_error;
        return;
    }

    free_fclose_for_write_result (add_file, delete_file, add_path, delete_path);
    return;
}

 void free_fclose_for_write_result (FILE *first_file, FILE *second_file, char *path_1, char *path_2)
 {
    if (first_file) fclose (first_file);
    if (second_file) fclose (second_file);
    if (path_1) free (path_1);
    if (path_2) free (path_2);
    return;    
 }

char *make_path (char *path, char *file_name, result_t *result)
{
    if (!path || !file_name)
    {
        ERR_PRINTF("null_argument_error");
        result->error_code = null_argument_error;
        return NULL;
    }

    char *path_to_file = (char *) malloc (MAX_PATH_LEN * sizeof (char));
    if (!path_to_file)
    {
        ERR_PRINTF("alloc_error");
        result->error_code = alloc_error;
        return NULL;
    }

    if (strlen (path) + strlen (file_name) + 2 >= MAX_PATH_LEN)
    {
        ERR_PRINTF("snprintf_overflow_error");
        result->error_code = snprintf_overflow_error;
        free (path_to_file);
        return NULL;
    }

    if (snprintf (path_to_file, MAX_PATH_LEN, "%s/%s", path, file_name) < 0)
    {
        ERR_PRINTF("snprintf_overflow_error");
        result->error_code = snprintf_overflow_error;
        free (path_to_file);
        return NULL;
    }
    return path_to_file;
}

error_code_t output_double_arr (FILE *output_file, double *arr, unsigned size)
{
    if (!output_file) 
    {
        ERR_PRINTF("fopen_error");
        return fopen_error;
    }
    if (!arr) return all_okey;

    for (unsigned i = 0; i < size; i++)
    {
        if (fprintf (output_file, "%lf\n", arr [i]) < 0)
        {
            ERR_PRINTF("output_error");
            return output_error;
        }
    }

    return all_okey;
}



void free_in_testing (double *add_time_arr, double *delete_time_arr, unsigned *test_arr, void *tree_ptr, destruct_func_t destruct_f)
{
    if (add_time_arr) free (add_time_arr);
    if (delete_time_arr) free (delete_time_arr);
    if (test_arr) free (test_arr);
    if (destruct_f && tree_ptr) destruct_f (tree_ptr);
    return;
}

clock_t feel_tree_by_arr (unsigned size, unsigned *test_arr, void *tree, result_t *result, add_func_t add_f)
{
    if (!result)
    {
        ERR_PRINTF("result_t *result == NULL");
        return -1;
    }
    if (!test_arr || !tree)
    {
        ERR_PRINTF("null_argument_error");
        result->error_code = null_argument_error;
        return -1;
    }    
    
    error_code_t error_code = all_okey;
    clock_t time = clock ();

    for (unsigned i = 0; i < size; i++)
    {
        error_code = add_f (tree, test_arr [i]);
        
        if (error_code) 
        {
            ERR_PRINTF("add_f err");
            result->error_code = error_code;
            return -1;
        }
    }
    time = clock () - time;
    return time;
}

clock_t delete_from_tree_by_arr (unsigned size, unsigned *test_arr, void *tree, result_t *result, delete_func_t delete_f)
{
    assert (result);
    if (!test_arr || !tree)
    {
        ERR_PRINTF("null_argument_error");
        result->error_code = null_argument_error;
        return -1;
    }
    error_code_t error_code = all_okey;
    clock_t time = clock ();

    for (unsigned i = 0; i < size; i++)
    {
        error_code = delete_f (tree, test_arr [i]);
        
        if (error_code) 
        {
            ERR_PRINTF("delete_f err");
            result->error_code = error_code;
            return -1;
        }
    }
    time = clock () - time;
    return time;
}
