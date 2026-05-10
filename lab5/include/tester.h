#ifndef TESTER_H
#define TESTER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

#ifndef NDEBUG
#define ERR_PRINTF(fmt, ...) fprintf(stderr, ANSI_COLOR_YELLOW "[ERROR] %s:%d in %s: " fmt ANSI_COLOR_RESET "\n", \
                                   __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define ERR_PRINTF(fmt, ...) do {} while (0)
#endif
#define ITER_COUNT 5


typedef unsigned *(*test_gen_func_t) (unsigned);
typedef int       (*add_func_t)      (void *, unsigned);
typedef int       (*delete_func_t)   (void *, unsigned);
typedef void     *(*init_func_t)     ();
typedef void      (*destruct_func_t) (void *);

#define INIT_PATH_LEN 128
#define MAX_PATH_LEN  160

    typedef enum Error_code_t
    {
        all_okey = 0,
        alloc_error = 1,
        fopen_error = 2,
        output_error = 3,
        func_ptr_error = 4,
        test_gen_error = 5,
        make_path_error = 6,
        path_intit_error = 7,
        null_argument_error = 8,
        func_name_init_error = 9,
        snprintf_overflow_error = 10,
        path_length_exceeded_error = 11,
        incorrect_number_args_error = 12,


    } error_code_t;

typedef struct Interface_t
{
    add_func_t      add_f;
    init_func_t     init_f;
    delete_func_t   delete_f;
    destruct_func_t destruct_f;
    test_gen_func_t test_gen_f;
    char _path [INIT_PATH_LEN];
    unsigned from, to, step;
} interface_t;

typedef struct Result_t
{
    unsigned size;
    double *add_time;
    double *delete_time;
    error_code_t error_code;
} result_t;


error_code_t run                          (interface_t interface);
void         testing                      (interface_t interface, result_t *result);
void         write_result                 (interface_t interface, result_t result []);
char        *make_path                    (char *path, char *file_name, result_t *result);
error_code_t output_double_arr            (FILE *output_file, double *arr, unsigned size);
void         free_fclose_for_write_result (FILE *first_file, FILE *second_file, char *path_1, char *path_2);
clock_t      feel_tree_by_arr             (unsigned size, unsigned *test_arr, void *tree, result_t *result, add_func_t add_f);
clock_t      delete_from_tree_by_arr      (unsigned size, unsigned *test_arr, void *tree, result_t *result, delete_func_t delete_f);
void         free_in_testing              (double *add_time_arr, double *delete_time_arr, unsigned *test_arr, void *tree_ptr, destruct_func_t destruct_f);


#endif