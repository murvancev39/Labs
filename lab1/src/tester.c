#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arr_stack.h"
#include "list_stack.h"
#include <time.h>
#include <assert.h>

typedef struct
{
    void *(*stack_ctr) (size_t element_size);
    void *(*stack_dtr) (void *stack_ptr);
    int (*push) (void *stack_ptr, void *buffer);
    int (*top) (void *stack_ptr, void *buffer);
    int (*pop) (void *stack_ptr);
    int (*get_employment) (void *stack_ptr);
} stack_functions;


double test_1 (int num_elements, stack_functions *interface);
double test_2 (int num_elements, stack_functions *interface);
double test_3 (int num_elements, stack_functions *interface);
double test_4 (int num_elements, stack_functions *interface);



int main (int argc, char *argv[])
{
    srand (time (NULL));
    int arr_flag = 0, list_flag = 0;

    int g = 1;
    while (g < argc)
    {
        if (!strcmp (argv [g], "-A")) arr_flag = 1;
        if (!strcmp (argv [g], "-L")) list_flag = 1;
        g++;
    }
    
    if (arr_flag == 1)
    {
        printf ("run\n");
        FILE *first_arr = fopen ("first_arr_test.txt", "w");
        assert (first_arr);
        FILE *second_arr = fopen ("second_arr_test.txt", "w");
        assert (second_arr);
        FILE *third_arr = fopen ("third_arr_test.txt", "w");
        assert (third_arr);
        FILE *fourth_arr = fopen ("fourth_arr_test.txt", "w");
        assert (fourth_arr);

        stack_functions interface = {   
                                        arr_stack_ctr_for_tests,
                                        arr_stack_dtr,
                                        arr_push,
                                        arr_top,
                                        arr_pop,
                                        arr_get_employment
                                    };
        
        double test_result = 0;
        for (int num_elements = 1000; num_elements <= 1000000; num_elements+=1000)
        {
            test_result = test_1 (num_elements, &interface);
            fprintf (first_arr, "%d %lf\n", num_elements, test_result);
            
            test_result = test_2 (num_elements, &interface);
            fprintf (second_arr, "%d %lf\n", num_elements, test_result);
            
            test_result = test_3 (num_elements, &interface);
            fprintf (third_arr, "%d %lf\n", num_elements, test_result);
            
            test_result = test_4 (num_elements, &interface);
            fprintf (fourth_arr, "%d %lf\n", num_elements, test_result);
        }
        
        fclose (first_arr);
        fclose (second_arr);
        fclose (third_arr);
        fclose (fourth_arr);
    }
    
    if (list_flag == 1)
    {
        FILE *first_list = fopen ("first_list_test.txt", "w");
        assert (first_list);
        FILE *second_list = fopen ("second_list_test.txt", "w");
        assert (second_list);
        FILE *third_list = fopen ("third_list_test.txt", "w");
        assert (third_list);
        FILE *fourth_list = fopen ("fourth_list_test.txt", "w");
        assert (fourth_list);

        stack_functions interface = {   
                                        list_stack_ctr,
                                        list_stack_dtr,
                                        list_push,
                                        list_top,
                                        list_pop,
                                        list_get_employment
                                    };
        
        double test_result = 0;
        for (int num_elements = 1000; num_elements <= 1000000; num_elements+=1000)
        {
            test_result = test_1 (num_elements, &interface);
            fprintf (first_list, "%d %lf\n", num_elements, test_result);
            
            test_result = test_2 (num_elements, &interface);
            fprintf (second_list, "%d %lf\n", num_elements, test_result);
            
            test_result = test_3 (num_elements, &interface);
            fprintf (third_list, "%d %lf\n", num_elements, test_result);
            
            test_result = test_4 (num_elements, &interface);
            fprintf (fourth_list, "%d %lf\n", num_elements, test_result);
        }
        
        fclose (first_list);
        fclose (second_list);
        fclose (third_list);
        fclose (fourth_list);
    }
    
    return 0;
}

double test_1 (int num_elements, stack_functions *interface)
{
    double average_time = 0;
    
    for (int num_test = 0; num_test < 3; num_test++)
    {
        void *stack_ptr = interface->stack_ctr (sizeof (int));

        clock_t cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            interface->push (stack_ptr, &i);
        }

        while (interface->get_employment (stack_ptr) >= num_elements / 10)
        {
            int half = interface->get_employment (stack_ptr) / 2;
            int quarter = interface->get_employment (stack_ptr) / 4;
            for (int i = 0; i < half; i++)
            {
                interface->pop (stack_ptr);
            }
            for (int i = 0; i < quarter; i++)
            {
                interface->push (stack_ptr, &i);
            }
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;
        interface->stack_dtr (stack_ptr);
    }
    average_time /= 3;

    return (average_time / CLOCKS_PER_SEC);
}

double test_2 (int num_elements, stack_functions *interface)
{
    double average_time = 0;
    double average_test_1_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        void *stack_ptr = interface->stack_ctr (sizeof (int));

        clock_t cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            interface->push (stack_ptr, &i);

        }

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                interface->pop (stack_ptr);
            }
        }
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                interface->push (stack_ptr, &j);
            }
        }

        cur_time -= clock ();

        average_test_1_time += test_1 (num_elements, interface);

        cur_time += clock ();

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                interface->pop (stack_ptr);
            }
        }

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                interface->push (stack_ptr, &j);
            }
        }
        
        cur_time = clock () - cur_time;
        average_time += cur_time;
        interface->stack_dtr (stack_ptr);
    }
    average_time /= 3;

    average_test_1_time /= 3;

    return (average_time / CLOCKS_PER_SEC) + average_test_1_time;
}

double test_3 (int num_elements, stack_functions *interface)
{
    int random_value = 0;
    double average_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        void *stack_ptr = interface->stack_ctr (sizeof (int));

        for (int i = 0; i <= num_elements; i++)
        {
            interface->push (stack_ptr, &i);
        }

        clock_t cur_time = clock ();

        for (int i = 0; i < num_elements; i++)
        {
            random_value = rand ();
            if (random_value > (RAND_MAX / 2))
            {
                interface->pop (stack_ptr);
            }
            else
            {
                interface->push (stack_ptr, &random_value);
            }
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;
        
        interface->stack_dtr (stack_ptr);
    }
    average_time /= 3;
    
    return (average_time / CLOCKS_PER_SEC);
}

double test_4 (int num_elements, stack_functions *interface)
{
    double average_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        void *stack_ptr = interface->stack_ctr (sizeof (int));
        
        clock_t cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            interface->push (stack_ptr, &i);
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;

        interface->stack_dtr (stack_ptr);
    }

    average_time /= 3;

    return (average_time / CLOCKS_PER_SEC);
    
}