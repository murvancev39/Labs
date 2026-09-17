#ifndef TESTER_H
#define TESTER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test_gen.h"

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

typedef pair_t test_t;

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

typedef void         (*destruct_func_t)          (void *);
typedef test_t      *(*test_pairs_gen_func_t)    (unsigned, unsigned);
typedef unsigned    *(*test_sequence_gen_func_t) (unsigned, unsigned);
typedef error_code_t (*uni_op_func_t)            (void *, unsigned, unsigned);
typedef void        *(*init_with_feel_func_t)    (unsigned *arr, unsigned len);

#define INIT_PATH_LEN 128
#define MAX_PATH_LEN  160


typedef struct Interface_t
{
    char _path [INIT_PATH_LEN];
    unsigned from, to, step;
    uni_op_func_t            search_f;
    uni_op_func_t            update_f;
    destruct_func_t          destruct_f;
    init_with_feel_func_t    init_with_feel_f; 
    test_pairs_gen_func_t    test_pairs_gen_f; 
    test_sequence_gen_func_t test_sequence_gen_f;
} interface_t;

typedef struct Result_t
{
    unsigned size;
    double *search_time;
    error_code_t error_code;
} result_t;


error_code_t run                          (interface_t interface);
void         free_fclose_for_write_result (FILE *first_file, char *path_1);
void         testing                      (interface_t interface, result_t *result);
void         write_result                 (interface_t interface, result_t result []);
char        *make_path                    (char *path, char *file_name, result_t *result);
error_code_t output_double_arr            (FILE *output_file, double *arr, unsigned size);
void         free_in_testing              (double *time_arr, test_t *test_arr, unsigned *test_sequence, void *tree_ptr, destruct_func_t destruct_f);
clock_t      search_test_func             (unsigned size, test_t *test_arr, void *tree, result_t *result, uni_op_func_t search_f, uni_op_func_t update_f);

#endif