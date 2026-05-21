#include <stdio.h>
#include <stdlib.h>
#include "arr_stack.h"
#include "list_stack.h"
#include "status.h"

#define TESTS \
    ADD (test_array_stack_lifecycle) \
    ADD (test_array_stack_lifo_order) \
    ADD (test_array_stack_underflow) \
    ADD (test_list_stack_lifecycle) \
    ADD (test_list_stack_lifo_order) \
    ADD (test_list_stack_underflow)

#define CTEST_IMPLEMENTATION
#include "ctest.h"

// -------------------------------------------------------------------------
// ARR_STACK
// -------------------------------------------------------------------------

// создание, добавление элементов и подсчет
TEST (test_array_stack_lifecycle,
    void *stack_ptr = arr_stack_ctr_for_tests (sizeof (int));

    ASSERT_MSG (stack_ptr != NULL, "Array stack ptr must not be NULL after creation");
    ASSERT_EQ_MSG (0, arr_get_count (stack_ptr), "Init count for array stack must be 0");

    for (int i = 0; i < 1488; i++)
    {
        status_t res = arr_push (stack_ptr, &i);
        ASSERT_EQ_MSG (STATUS_OK, res, "Failed to push element into array stack");
    }

    ASSERT_EQ_MSG (1488, arr_get_count (stack_ptr), "Array stack count must be 1488 after 1488 pushes");

    arr_stack_dtr (stack_ptr);
)

// проверка на свйойство lifo
TEST (test_array_stack_lifo_order,
    void *stack_ptr = arr_stack_ctr_for_tests (sizeof (int));
    
    int val1 = 100;
    int val2 = 200;
    int val3 = 300;

    arr_push (stack_ptr, &val1);
    arr_push (stack_ptr, &val2);
    arr_push (stack_ptr, &val3);

    int output_val = 0;

    status_t top_res = arr_top (stack_ptr, &output_val);

    ASSERT_EQ_MSG (STATUS_OK, top_res, "arr_top failed to get element");
    ASSERT_EQ_MSG (300, output_val, "Top element must be 300");

    arr_pop (stack_ptr);
    arr_top (stack_ptr, &output_val);

    ASSERT_EQ_MSG (200, output_val, "Top element must be 200 after one pop");


    arr_pop (stack_ptr);
    arr_top (stack_ptr, &output_val);
    ASSERT_EQ_MSG (100, output_val, "Top element must be 100 after two pops");

    arr_stack_dtr (stack_ptr);
)

// проверка на повторный поп
TEST (test_array_stack_underflow,
    void *stack_ptr = arr_stack_ctr_for_tests (sizeof (int));
    

    status_t pop_res = arr_pop (stack_ptr);

    ASSERT_EQ_MSG (STATUS_ERR, pop_res, "arr_pop on empty stack must return STATUS_ERR");


    int val = 0;
    status_t top_res = arr_top (stack_ptr, &val);
    
    ASSERT_EQ_MSG (STATUS_ERR, top_res, "arr_top on empty stack must return STATUS_ERR");

    arr_stack_dtr (stack_ptr);
)

// -------------------------------------------------------------------------
// LIST_STACK
// -------------------------------------------------------------------------

// создание, добавление элементов и подсчет
TEST (test_list_stack_lifecycle,
    void *stack_ptr = list_stack_ctr (sizeof (int));

    ASSERT_MSG (stack_ptr != NULL, "List stack ptr must not be NULL after creation");
    ASSERT_EQ_MSG (0, list_get_count (stack_ptr), "Init count for list stack must be 0");

    for (int i = 0; i < 1488; i++)
    {
        status_t res = list_push (stack_ptr, &i);
        ASSERT_EQ_MSG (STATUS_OK, res, "Failed to push element into list stack");
    }

    ASSERT_EQ_MSG (1488, list_get_count (stack_ptr), "List stack count must be 1488 after 1488 pushes");

    list_stack_dtr (stack_ptr);
)

// проверка на свойство lifo
TEST (test_list_stack_lifo_order,
    void *stack_ptr = list_stack_ctr (sizeof (int));
    
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;

    list_push (stack_ptr, &val1);
    list_push (stack_ptr, &val2);
    list_push (stack_ptr, &val3);

    int output_val = 0;

    status_t top_res = list_top (stack_ptr, &output_val);

    ASSERT_EQ_MSG (STATUS_OK, top_res, "list_top failed to get element");
    ASSERT_EQ_MSG (30, output_val, "Top element must be 30");

    list_pop (stack_ptr);
    list_top (stack_ptr, &output_val);

    ASSERT_EQ_MSG (20, output_val, "Top element must be 20 after one pop");

    list_pop (stack_ptr);
    list_top (stack_ptr, &output_val);

    ASSERT_EQ_MSG (10, output_val, "Top element must be 10 after two pops");

    list_stack_dtr (stack_ptr);
)

// проверка на повторный поп
TEST (test_list_stack_underflow,
    void *stack_ptr = list_stack_ctr (sizeof (int));
    
    status_t pop_res = list_pop (stack_ptr);

    ASSERT_EQ_MSG (STATUS_ERR, pop_res, "list_pop on empty stack must return STATUS_ERR");

    int val = 0;
    status_t top_res = list_top (stack_ptr, &val);

    ASSERT_EQ_MSG (STATUS_ERR, top_res, "list_top on empty stack must return STATUS_ERR");

    list_stack_dtr (stack_ptr);
)


RUN_TESTS ();