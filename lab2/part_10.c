#include "tester.h"
#include "quadratic_sorts.h"
#include "heap_sort.h"
#include "merge_sort.h"
#include "quick_sorts_pivot.h"


int compare (const void *a, const void *b);
void std_qsort (unsigned *arr, size_t size);

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 1000000
#define BIG_STEP 10000

int main ()
{
    run_tests ("tests/big_tests/", "std_quick", std_qsort, "tests_results/part_10/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("std qsort | big_tests ---- completed\n");
    
    run_tests ("tests/big_tests/", "heap_3_", heap_sort_bottom_up_3, "tests_results/part_10/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("heap sort bottom up 3 | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "rand_hoar_quick", quick_sort_hoar_rand , "tests_results/part_10/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("hoar quick sort rand | big_tests ---- completed\n");

    run_tests ("tests/big_tests/", "recursive_merge", merge_sort_recursive, "tests_results/part_10/big_tests/", BIG_SIZE, BIG_STEP);
    printf ("recursive merge sort | big_tests ---- completed\n");
    
    printf ("--------------Big tests completed--------------\n");
    return 0;
    
}

int compare (const void *a, const void *b) 
{
    return (*(unsigned *) a - *(unsigned *) b);
}

void std_qsort (unsigned *arr, size_t size)
{
    qsort (arr, size, sizeof (unsigned), compare);
}