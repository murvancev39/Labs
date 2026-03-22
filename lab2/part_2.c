#include "tester.h"
#include "heap_sort.h"

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 10000

int main ()
{
    // run_tests ("tests/small_tests/", "heap_2_", heap_sort_bottom_up_2, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 2 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_3_", heap_sort_bottom_up_3, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 3 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_4_", heap_sort_bottom_up_4, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 4 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_5_", heap_sort_bottom_up_5, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 5 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_6_", heap_sort_bottom_up_6, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 6 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_7_", heap_sort_bottom_up_7, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 7 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_8_", heap_sort_bottom_up_8, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 8 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_9_", heap_sort_bottom_up_9, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 9 | small_tests ---- completed\n");

    // run_tests ("tests/small_tests/", "heap_10_", heap_sort_bottom_up_10, "tests_results/part_2/small_tests/", SMALL_SIZE, SMALL_STEP);
    // printf ("heap sort bottom up 10 | small_tests ---- completed\n");

    // printf ("--------------Small tests completed--------------\n");

    run_tests ("tests/big_tests/", "heap_2_", heap_sort_bottom_up_2, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 2 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_3_", heap_sort_bottom_up_3, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 3 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_4_", heap_sort_bottom_up_4, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 4 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_5_", heap_sort_bottom_up_5, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 5 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_6_", heap_sort_bottom_up_6, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 6 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_7_", heap_sort_bottom_up_7, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 7 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_8_", heap_sort_bottom_up_8, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 8 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_9_", heap_sort_bottom_up_9, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 9 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "heap_10_", heap_sort_bottom_up_10, "tests_results/part_2/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 10 | big_tests ---- completed\n");

    printf ("--------------Big tests completed--------------\n");

    // run_tests ("tests/test_most_dublicates/", "heap_2_", heap_sort_bottom_up_2, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 2 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_3_", heap_sort_bottom_up_3, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 3 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_4_", heap_sort_bottom_up_4, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 4 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_5_", heap_sort_bottom_up_5, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 5 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_6_", heap_sort_bottom_up_6, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 6 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_7_", heap_sort_bottom_up_7, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 7 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_8_", heap_sort_bottom_up_8, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 8 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_9_", heap_sort_bottom_up_9, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 9 | test_most_dublicates ---- completed\n");

    // run_tests ("tests/test_most_dublicates/", "heap_10_", heap_sort_bottom_up_10, "tests_results/part_2/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    // printf ("heap sort bottom up 10 | test_most_dublicates ---- completed\n");

    return 0;
    
}
