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
    
    if (result->search_time) free (result->search_time);
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
    srand (42);

    uni_op_func_t            search_f            = interface.search_f;
    uni_op_func_t            update_f            = interface.update_f;
    destruct_func_t          destruct_f          = interface.destruct_f;
    init_with_feel_func_t    init_f              = interface.init_with_feel_f;
    test_pairs_gen_func_t    test_pairs_gen_f    = interface.test_pairs_gen_f;
    test_sequence_gen_func_t test_sequence_gen_f = interface.test_sequence_gen_f;

    if (!search_f || !init_f || !destruct_f || !test_pairs_gen_f || !test_sequence_gen_f) 
    { // в проверке нет update тк тестирование может проходить и с ним и без него
        ERR_PRINTF("func_ptr_error");
        result->error_code = func_ptr_error;
        return;
    }
    
    unsigned count_times = ((interface.to - interface.from) / interface.step) + 1;
    double *time_arr     = (double *) calloc (count_times, sizeof (double));
    result->size         = count_times;
    result->search_time  = NULL;
    
    clock_t time = 0;
    clock_t all_time = 0;
    void *tree = NULL;
    test_t *test_pairs_arr = NULL;
    unsigned *test_sequence = NULL;
    

    int cur_idx = 0;
    for (unsigned size = interface.from; size <= interface.to; size += interface.step)
    {
        printf ("[SIZE] - %u\n", size);
        all_time = 0;
        
        for (int k = 0; k < ITER_COUNT; k++)
        {
            test_pairs_arr = test_pairs_gen_f (size, size);
            test_sequence  = test_sequence_gen_f (size, RAND_MAX);
            if (!test_pairs_arr || !test_sequence)
            {
                free_in_testing (time_arr, test_pairs_arr, test_sequence, tree, destruct_f);
                result->search_time = NULL;
                ERR_PRINTF("alloc_error");
                result->error_code = alloc_error;
                return;
            }
            
            tree = init_f (test_sequence, size);
            if (!tree) 
            {
                free_in_testing (time_arr, test_pairs_arr, test_sequence, tree, destruct_f);
                ERR_PRINTF("alloc_error");
                result->error_code = alloc_error;
                return;
            }
            // testing
            // ---------------------------------------------------------------------------------------- 
            time = search_test_func (size, test_pairs_arr, tree, result, search_f, update_f);
            if (result->error_code)
            {
                ERR_PRINTF("search_test_func err");
                free_in_testing (time_arr, test_pairs_arr, test_sequence, tree, destruct_f);
                return;
            }
            all_time += time;
            // ----------------------------------------------------------------------------------------
            free_in_testing (NULL, test_pairs_arr, test_sequence, tree, destruct_f);
            tree = NULL;
            test_pairs_arr = NULL;
            test_sequence  = NULL;
        }
        
        time_arr [cur_idx] = (((double) all_time) / CLOCKS_PER_SEC ) / ITER_COUNT;
        cur_idx++;
        printf ("\r");
    }

    result->search_time  = time_arr;
    return;
}

void write_result (interface_t interface, result_t result [])
{
    if (!result) 
    {
        ERR_PRINTF("result_t *result == NULL");
        return;
    }

    char *search_path = NULL;

    if (result->search_time != NULL)
    {
        search_path = make_path (interface._path, "search.txt", result);
        if (!search_path) 
        {
            ERR_PRINTF("search_path == NULL");
            return;
        }
    }

    FILE *search_file = NULL;
    if (search_path) search_file = fopen (search_path, "w");

    if (search_file)
    {
        result->error_code = output_double_arr (search_file, result->search_time, result->size);
        if (result->error_code) 
        {
            ERR_PRINTF("output_double_arr err");
            free_fclose_for_write_result (search_file, search_path);
            return;
        }
    }
    else
    {
        ERR_PRINTF("fopen_error");
        result->error_code = fopen_error;
        free_fclose_for_write_result (search_file, search_path);
        return;
    }
    free_fclose_for_write_result (search_file, search_path);
    return;
}

void free_fclose_for_write_result (FILE *first_file, char *path_1)
{
if (first_file) fclose (first_file);
if (path_1) free (path_1);
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

void free_in_testing (double *time_arr, test_t *test_arr, unsigned *test_sequence, void *tree_ptr, destruct_func_t destruct_f)
{
    if (time_arr)      free (time_arr);
    if (test_arr)      free (test_arr);
    if (test_sequence) free (test_sequence);
    if (destruct_f && tree_ptr) destruct_f (tree_ptr);
    return;
}

clock_t search_test_func (unsigned size, test_t *test_arr, void *tree, result_t *result, uni_op_func_t search_f, uni_op_func_t update_f)
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
    if (!search_f)
    {
        ERR_PRINTF("search_f ptr is NULL");
        result->error_code = func_ptr_error;
        return -1;
    }    
    
    error_code_t error_code = all_okey;
    clock_t time = clock ();

    if (update_f)
    {
        for (unsigned i = 0; i < size; i++)
        {
            if (rand () % 2) error_code = search_f (tree, test_arr [i].left, test_arr [i].right);
            else             error_code = update_f (tree, test_arr [i].left, test_arr [i].right);
            if (error_code) 
            {
                ERR_PRINTF("search_f or updatet_f err");
                result->error_code = error_code;
                return -1;
            }
        }
    }
    else
    {
        for (unsigned i = 0; i < size; i++)
        {
            error_code = search_f (tree, test_arr [i].left, test_arr [i].right);
            
            if (error_code) 
            {
                ERR_PRINTF("add_f err");
                result->error_code = error_code;
                return -1;
            }
        }
    }
    time = clock () - time;
    return time;
}
