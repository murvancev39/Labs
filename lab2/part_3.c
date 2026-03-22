#include "tester.h"
#include "merge_sort.h"

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 10000

int main ()
{
    run_tests ("tests/big_tests/", "iterative_merge", merge_sort_iterative, "tests_results/part_3/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("iterative merge sort | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "recursive_merge", merge_sort_recursive, "tests_results/part_3/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("recursive merge sort | big_tests ---- completed\n");

    printf ("--------------Big tests completed--------------\n");

    return 0;
    
}
