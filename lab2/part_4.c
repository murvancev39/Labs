#include "tester.h"
#include "quick_sorts_partition.h"

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 10000

int main ()
{
    run_tests ("tests/big_tests/", "hoar_quick", quick_sort_hoar, "tests_results/part_4/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "lomuto_quick", quick_sort_lomuto, "tests_results/part_4/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("lomuto quick sort | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "fat_quick", quick_sort_fat, "tests_results/part_4/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("fat quick sort | big_tests ---- completed\n");

    printf ("--------------Big tests completed--------------\n");

    run_tests ("tests/test_most_dublicates/", "hoar_quick", quick_sort_hoar, "tests_results/part_4/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort | test_most_dublicates ---- completed\n");

    run_tests ("tests/test_most_dublicates/", "lomuto_quick", quick_sort_lomuto, "tests_results/part_4/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    printf ("lomuto quick sort | test_most_dublicates ---- completed\n");

    run_tests ("tests/test_most_dublicates/", "fat_quick", quick_sort_fat, "tests_results/part_4/test_most_dublicates/", BIG_SIZE, BIG_STEP);
    printf ("fat quick sort | test_most_dublicates ---- completed\n");

    return 0;
    
}
