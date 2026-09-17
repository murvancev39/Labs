#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_f_part_1.h"
#include "hash_f_part_2.h"
#include "hash_f_part_3.h"
#include "hash_table_chained.h"
#include "test_generate.h"

#define MILLION 1000000
#define TABLE_SIZE 100

typedef struct
{
    unsigned (*hash_func)(void *);
    char func_name [11];
} interface;

void strings_arr_dtr (char **arr, size_t size);

int main (int argc, char *argv[])
{
    int flag_u = 0;
    int flag_f = 0;
    int flag_s = 0;

    for (int k = 1; k < argc; k++)
    {
        if (argv [k] != NULL)
        {
            if (!strcmp(argv [k], "-U")) flag_u = 1;
            if (!strcmp(argv [k], "-S")) flag_s = 1;
            if (!strcmp(argv [k], "-F")) flag_f = 1;
        }
    }
    
    if (flag_u)
    {
        unsigned *arr = unsigned_test_gen (MILLION);
        if (arr != NULL)
        {
            interface cur_interface [3] = {{hash_f_u_bits, "BITS"}, {hash_f_u_rem, "REMAIND"}, {hash_f_u_knuth, "KNUTH"}};
            for (int k = 0; k < 3; k++)
            {
                printf ("### TEST: UNSIGNED_%s\n", cur_interface [k].func_name);
                chained_hash_table_t *table = chained_hash_table_ctr (TABLE_SIZE, 0, cur_interface [k].hash_func, unsigned_cmp);
                
                if (table != NULL)
                {
                    for (unsigned i = 0; i < MILLION; i++) chained_hash_table_add (table, arr + i);
                    
                    if (table->collision_arr != NULL)
                    {
                        for (unsigned i = 0; i < TABLE_SIZE; i++) 
                        {
                            if (table->collision_arr [i]) printf ("%u %u\n", i, table->collision_arr [i]);
                        }
                    }
                    chained_hash_table_dtr (table);
                }
            }
            free (arr);
        }
    }

    if (flag_f)
    {
        float *arr = float_test_gen (MILLION);
        if (arr != NULL)
        {
            interface cur_interface [5] = {{hash_f_f_int, "INT"}, {hash_f_f_union, "BITS"},
            {hash_f_f_exp, "EXP"}, {hash_f_f_mantiss, "MANTISSA"}, {hash_f_f_mant_exp, "EXP_MANTIS"}};
            for (int k = 0; k < 5; k++)
            {
                printf ("### TEST: FLOAT_%s\n", cur_interface [k].func_name);
                chained_hash_table_t *table = chained_hash_table_ctr (TABLE_SIZE, 0, cur_interface [k].hash_func, float_cmp);
                
                if (table != NULL)
                {
                    for (unsigned i = 0; i < MILLION; i++) chained_hash_table_add (table, arr + i);
                    
                    if (table->collision_arr != NULL)
                    {
                        for (unsigned i = 0; i < TABLE_SIZE; i++)
                        {
                            if (table->collision_arr [i]) printf ("%u %u\n", i, table->collision_arr [i]);
                        }
                    }
                    chained_hash_table_dtr (table);
                }
            }
            free (arr);
        }
    }

    if (flag_s)
    {
        char **arr = string_test_gen (MILLION);
        if (arr != NULL)
        {
            interface cur_interface [4] = {{hash_f_s_len, "LEN"}, {hash_f_s_sum, "SUM"},
            {hash_f_s_polinom, "POLINOM"}, {hash_f_s_src32, "SRC_32"}};
            for (int k = 0; k < 4; k++)
            {
                printf ("### TEST: STRINGS_%s\n", cur_interface [k].func_name);
                chained_hash_table_t *table = chained_hash_table_ctr (TABLE_SIZE, 0, cur_interface [k].hash_func, string_cmp);
                
                if (table != NULL)
                {
                    for (unsigned i = 0; i < MILLION; i++) chained_hash_table_add (table, arr [i]);
                    
                    if (table->collision_arr != NULL)
                    {
                        for (unsigned i = 0; i < TABLE_SIZE; i++) 
                        {
                            if (table->collision_arr [i]) printf ("%u %u\n", i, table->collision_arr [i]);
                        }
                    }
                    chained_hash_table_dtr (table);
                }
            }
            strings_arr_dtr (arr, MILLION);
        }
    }
    return 0;
}

void strings_arr_dtr (char **arr, size_t size)
{
    if (!arr) return;
    for (size_t i = 0; i < size; i++)
    {
        free (arr [i]);
    }
    free (arr);
}