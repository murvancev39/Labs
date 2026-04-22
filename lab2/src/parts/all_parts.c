#include "all_parts.h"

int main (int argc, char *argv [])
{
    if (argc < 4) return 0;

    char tests_dir_path [32] = {};
    char res_dir_path [32] = {};
    strcpy (tests_dir_path, argv [1]);
    strcpy (res_dir_path, argv [2]);
    
    int part_1_flag  = 0;
    int part_2_flag  = 0;    
    int part_3_flag  = 0;
    int part_4_flag  = 0;
    int part_5_flag  = 0;
    int part_10_flag = 0;

    for (int i = 3; i < argc; i++)
    {
        if (!strcmp (argv [i], "--part_1"))  part_1_flag  = 1;
        if (!strcmp (argv [i], "--part_2"))  part_2_flag  = 1;
        if (!strcmp (argv [i], "--part_3"))  part_3_flag  = 1;
        if (!strcmp (argv [i], "--part_4"))  part_4_flag  = 1;
        if (!strcmp (argv [i], "--part_5"))  part_5_flag  = 1;
        if (!strcmp (argv [i], "--part_10")) part_10_flag = 1;
        if (!strcmp (argv [i], "--all"))
        {
            part_1_flag  = 1;
            part_2_flag  = 1;
            part_3_flag  = 1;
            part_4_flag  = 1;
            part_5_flag  = 1;
            part_10_flag = 1;
        } 
    }
    int ind = 0;

    if (part_1_flag) ind = run_part_1 (res_dir_path, tests_dir_path);
    if (ind) return 1;

    if (part_2_flag) ind = run_part_2 (res_dir_path, tests_dir_path);
    if (ind) return 2;

    if (part_3_flag) ind = run_part_3 (res_dir_path, tests_dir_path);
    if (ind) return 3;

    if (part_4_flag) ind = run_part_4 (res_dir_path, tests_dir_path);
    if (ind) return 4;

    if (part_5_flag) ind = run_part_5 (res_dir_path, tests_dir_path);
    if (ind) return 5;

    if (part_10_flag) ind = run_part_10 (res_dir_path, tests_dir_path);
    if (ind) return 10;

    return 0;
}



int run_part_1 (char res_dir_path [], char tests_dir_path [])
{
    test_interface interface [4] = 
    {
        {"", "insertion", insertion_sort, "", SMALL_SIZE, SMALL_STEP},
        {"", "buble", bubble_sort, "", SMALL_SIZE, SMALL_STEP},
        {"", "selection", selection_sort, "", SMALL_SIZE, SMALL_STEP},
        {"", "shell", shell_sort, "", SMALL_SIZE, SMALL_STEP}
    };
    for (int i = 0; i < 4; i++)
    {
        snprintf (interface [i].path_tests_from, sizeof (interface [i].path_tests_from), 
                        "%s/small_tests/", tests_dir_path);
        snprintf (interface [i].path_tests_to, sizeof (interface [i].path_tests_to), 
                        "%s/part_1/small_tests", res_dir_path);
    }
    int indicator = 1;
    for (int i = 0; i < 4; i++)
    {
        indicator = run_tests  (interface [i].path_tests_from,
                                interface [i].func_name,
                                interface [i].sort_f,
                                interface [i].path_tests_to,
                                interface [i].test_size,
                                interface [i].test_step);
        if (!indicator) return 1; //TODO проверка в мейке
        printf ("[SMALL TESTS] - COMPLETED : %s sort\n", interface [i].func_name);
    }
    
    printf ("--------------[ALL SMALL TESTS COMPLETED]--------------\n");
    
    return 0;
}

int run_part_2 (char res_dir_path [], char tests_dir_path [])
{
    test_interface big_tests_interface [9] = 
    {
        {"", "heap_2", heap_sort_bottom_up_2, "", BIG_SIZE, BIG_STEP},
        {"", "heap_3", heap_sort_bottom_up_3, "", BIG_SIZE, BIG_STEP},
        {"", "heap_4", heap_sort_bottom_up_4, "", BIG_SIZE, BIG_STEP},
        {"", "heap_5", heap_sort_bottom_up_5, "", BIG_SIZE, BIG_STEP},
        {"", "heap_6", heap_sort_bottom_up_6, "", BIG_SIZE, BIG_STEP},
        {"", "heap_7", heap_sort_bottom_up_7, "", BIG_SIZE, BIG_STEP},
        {"", "heap_8", heap_sort_bottom_up_8, "", BIG_SIZE, BIG_STEP},
        {"", "heap_9", heap_sort_bottom_up_9, "", BIG_SIZE, BIG_STEP},
        {"", "heap_10", heap_sort_bottom_up_10, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 9; i++)
    {
        snprintf (big_tests_interface [i].path_tests_from, sizeof (big_tests_interface [i].path_tests_from),
                        "%s/big_tests/", tests_dir_path);
        snprintf (big_tests_interface [i].path_tests_to, sizeof (big_tests_interface [i].path_tests_to),
                        "%s/part_2/big_tests", res_dir_path);
    }

    int indicator = 1;
    for (int i = 0; i < 9; i++)
    {
        indicator = run_tests ( big_tests_interface [i].path_tests_from,
                                big_tests_interface [i].func_name,
                                big_tests_interface [i].sort_f,
                                big_tests_interface [i].path_tests_to,
                                big_tests_interface [i].test_size,
                                big_tests_interface [i].test_step);
        // printf ("\n\nEBLAN\n\n");
        if (!indicator) return 1;

        printf ("[BIG TESTS] - COMPLETED : %s sort\n", big_tests_interface [i].func_name);
    }
    
    printf ("--------------[ALL BIG TESTS COMPLETED]--------------\n");
    return 0;
}

int run_part_3 (char res_dir_path [], char tests_dir_path [])
{
    test_interface merge_tests_interface [2] = 
    {
        {"", "iterative_merge", merge_sort_iterative, "", BIG_SIZE, BIG_STEP},
        {"", "recursive_merge", merge_sort_recursive, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 2; i++)
    {
        snprintf (merge_tests_interface [i].path_tests_from, sizeof (merge_tests_interface [i].path_tests_from),
                                "%s/big_tests/", tests_dir_path);
        snprintf (merge_tests_interface [i].path_tests_to, sizeof (merge_tests_interface [i].path_tests_to),
                                "%s/part_3/big_tests", res_dir_path);
    }
    
    int indicator = 1;
    for (int i = 0; i < 2; i++)
    {
        indicator = run_tests  (merge_tests_interface [i].path_tests_from,
                                merge_tests_interface [i].func_name,
                                merge_tests_interface [i].sort_f,
                                merge_tests_interface [i].path_tests_to,
                                merge_tests_interface [i].test_size,
                                merge_tests_interface [i].test_step);
        
        if (!indicator) return 1;

        printf ("[BIG TESTS] - COMPLETED : %s sort\n", merge_tests_interface [i].func_name);
    }
    
    printf ("--------------[ALL BIG TESTS COMPLETED]--------------\n");

    return 0;
}

int run_part_4 (char res_dir_path [], char tests_dir_path [])
{
    test_interface quick_tests_interface [3] = 
    {
        {"", "hoar_quick", quick_sort_hoar, "", BIG_SIZE, BIG_STEP},
        {"", "lomuto_quick", quick_sort_lomuto, "", BIG_SIZE, BIG_STEP},
        {"", "fat_quick", quick_sort_fat, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 3; i++)
    {
        snprintf (quick_tests_interface [i].path_tests_from, sizeof (quick_tests_interface [i].path_tests_from),
                            "%s/big_tests/", tests_dir_path);
        snprintf (quick_tests_interface [i].path_tests_to, sizeof (quick_tests_interface [i].path_tests_to),
                            "%s/part_4/big_tests", res_dir_path);
    }
    int indicator = 1;
    for (int i = 0; i < 3; i++)
    {
        indicator = run_tests  (quick_tests_interface [i].path_tests_from,
                                quick_tests_interface [i].func_name,
                                quick_tests_interface [i].sort_f,
                                quick_tests_interface [i].path_tests_to,
                                quick_tests_interface [i].test_size,
                                quick_tests_interface [i].test_step);
        
        if (!indicator) return 1;

        printf ("[BIG TESTS] - COMPLETED : %s sort\n", quick_tests_interface [i].func_name);
    }
    
    printf ("--------------[ALL BIG TESTS COMPLETED]--------------\n");

    test_interface quick_dublicates_interface [3] = 
    {
        {"", "hoar_quick", quick_sort_hoar, "", BIG_SIZE, BIG_STEP},
        {"", "lomuto_quick", quick_sort_lomuto, "", BIG_SIZE, BIG_STEP},
        {"", "fat_quick", quick_sort_fat, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 3; i++)
    {
        snprintf (quick_dublicates_interface [i].path_tests_from, sizeof (quick_tests_interface [i].path_tests_from), 
                                    "%s/most_dub_tests/", tests_dir_path);
        snprintf (quick_dublicates_interface [i].path_tests_to, sizeof (quick_tests_interface [i].path_tests_to),
                                    "%s/part_4/most_dub_tests", res_dir_path);
    }

    indicator = 1;
    for (int i = 0; i < 3; i++)
    {
        indicator = run_tests  (quick_dublicates_interface [i].path_tests_from,
                                quick_dublicates_interface [i].func_name,
                                quick_dublicates_interface [i].sort_f,
                                quick_dublicates_interface [i].path_tests_to,
                                quick_dublicates_interface [i].test_size,
                                quick_dublicates_interface [i].test_step);
        
        if (!indicator) return 1;

        printf ("[MOST DUBLICATES TESTS] - COMPLETED : %s sort\n", quick_dublicates_interface [i].func_name);
    }
    
    printf ("--------------[ALL MOST DUBLICATES COMPLETED]--------------\n");

    return 0;
}

int run_part_5 (char res_dir_path [], char tests_dir_path [])
{
    test_interface hoar_pivots_interface [5] = 
    {
        {"", "hoar_quick_mid", quick_sort_hoar, "", BIG_SIZE, BIG_STEP},
        {"", "med_3_rand_hoar_quick", quick_sort_hoar_med_3_rand, "", BIG_SIZE, BIG_STEP},
        {"", "med_of_med_hoar_quick", quick_sort_hoar_med_of_med, "", BIG_SIZE, BIG_STEP},
        {"", "med_of_three_hoar_quick", quick_sort_hoar_med_of_three, "", BIG_SIZE, BIG_STEP},
        {"", "rand_hoar_quick", quick_sort_hoar_rand, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 5; i++)
    {
        snprintf (hoar_pivots_interface [i].path_tests_from, sizeof (hoar_pivots_interface [i].path_tests_from),
                            "%s/big_tests/", tests_dir_path);
        snprintf (hoar_pivots_interface [i].path_tests_to, sizeof (hoar_pivots_interface [i].path_tests_to),
                            "%s/part_5/big_tests", res_dir_path);
    }

    int indicator = 1;
    for (int i = 0; i < 5; i++)
    {
        indicator = run_tests  (hoar_pivots_interface [i].path_tests_from,
                                hoar_pivots_interface [i].func_name,
                                hoar_pivots_interface [i].sort_f,
                                hoar_pivots_interface [i].path_tests_to,
                                hoar_pivots_interface [i].test_size,
                                hoar_pivots_interface [i].test_step);
        
        if (!indicator) return 1;

        printf ("[BIG TESTS] - COMPLETED : %s sort\n", hoar_pivots_interface [i].func_name);
    }
    
    printf ("--------------[ALL BIG TESTS COMPLETED]--------------\n");
    return 0;
}

int run_part_10 (char res_dir_path [], char tests_dir_path [])
{
    test_interface mixed_tests_interface [4] = 
    {
        {"", "std_quick", std_qsort, "", BIG_SIZE, BIG_STEP},
        {"", "heap_3", heap_sort_bottom_up_3, "", BIG_SIZE, BIG_STEP},
        {"", "rand_hoar_quick", quick_sort_hoar_rand, "", BIG_SIZE, BIG_STEP},
        {"", "recursive_merge", merge_sort_recursive, "", BIG_SIZE, BIG_STEP}
    };

    for (int i = 0; i < 4; i++)
    {
        snprintf (mixed_tests_interface [i].path_tests_from, sizeof (mixed_tests_interface [i].path_tests_from),
                            "%s/big_tests/", tests_dir_path);
        snprintf (mixed_tests_interface [i].path_tests_to, sizeof (mixed_tests_interface [i].path_tests_to),
                            "%s/part_10/big_tests", res_dir_path);
    }

    int indicator = 1;
    for (int i = 0; i < 4; i++)
    {
        indicator = run_tests  (mixed_tests_interface [i].path_tests_from,
                                mixed_tests_interface [i].func_name,
                                mixed_tests_interface [i].sort_f,
                                mixed_tests_interface [i].path_tests_to,
                                mixed_tests_interface [i].test_size,
                                mixed_tests_interface [i].test_step);
        
        if (!indicator) return 1;

        printf ("[BIG TESTS] - COMPLETED : %s sort\n", mixed_tests_interface [i].func_name);
    }
    
    printf ("--------------[ALL BIG TESTS COMPLETED]--------------\n");
    return 0;
}

int int_compare (const void *a, const void *b) 
{
    if (*(unsigned *) a < *(unsigned *) b) return -1;
    if (*(unsigned *) a == *(unsigned *) b) return 0;
    return 1;
}

void std_qsort (unsigned *arr, size_t size)
{
    qsort (arr, size, sizeof (unsigned), int_compare);
}