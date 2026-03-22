#include "tester.h"
#include "quadratic_sorts.h"

#define SMALL_SIZE 1000
#define SMALL_STEP 50

#define BIG_SIZE 100000
#define BIG_STEP 5000

int main ()
{
    run_tests ("tests/small_tests/", "insertion", insertion_sort, "tests_results/part_1/small_tests/", SMALL_SIZE, SMALL_STEP);
    printf ("Insertion sort | small_tests ---- completed\n");

    run_tests ("tests/small_tests/", "buble", bubble_sort, "tests_results/part_1/small_tests/", SMALL_SIZE, SMALL_STEP);
    printf ("Buble sort | small_tests ---- completed\n");
    
    run_tests ("tests/small_tests/", "selection", selection_sort, "tests_results/part_1/small_tests/", SMALL_SIZE, SMALL_STEP);
    printf ("Selection sort | small_tests ---- completed\n");

    run_tests ("tests/small_tests/", "shell", shell_sort, "tests_results/part_1/small_tests/", SMALL_SIZE, SMALL_STEP);
    printf ("Shell sort | small_tests ---- completed\n");
    
    printf ("--------------Small tests completed--------------\n");
    
    return 0;
}
