#include "tester.h"
#include "quick_sorts_pivot.h"

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 10000

int main ()
{
    run_tests ("tests/big_tests/", "hoar_quick_mid", quick_sort_hoar, "tests_results/part_5/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort mid | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "med_3_rand_hoar_quick", quick_sort_hoar_med_3_rand, "tests_results/part_5/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort median of 3 rand | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "med_of_med_hoar_quick", quick_sort_hoar_med_of_med, "tests_results/part_5/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort median of median | big_tests ---- completed\n");
    
    run_tests ("tests/big_tests/", "med_of_three_hoar_quick", quick_sort_hoar_med_of_three, "tests_results/part_5/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort median of 3 not rand | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "rand_hoar_quick", quick_sort_hoar_rand , "tests_results/part_5/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort rand | big_tests ---- completed\n");

    printf ("--------------Big tests completed--------------\n");
    return 0;
    
}