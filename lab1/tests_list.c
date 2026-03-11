#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"
#include <time.h>
#include <assert.h>

double test1 (int num_elements);
double test2 (int num_elements);
double test3 (int num_elements);
double test4 (int num_elements);

int main ()
{
    srand (time (NULL));

    FILE *first = fopen ("first_test.txt", "a");
    assert (first);
    FILE *second = fopen ("second_test.txt", "a");
    assert (second);
    FILE *third = fopen ("third_test.txt", "a");
    assert (third);
    FILE *fourth = fopen ("fourth_test.txt", "a");
    assert (fourth);

    double test_result = 0;
    for (int num_elements = 1000; num_elements <= 1000000; num_elements+=1000)
    {
        test_result = test1 (num_elements);
        fprintf (first, "%d %lf\n", num_elements, test_result);

        test_result = test2 (num_elements);
        fprintf (second, "%d %lf\n", num_elements, test_result);

        test_result = test3 (num_elements);
        fprintf (third, "%d %lf\n", num_elements, test_result);

        test_result = test4 (num_elements);
        fprintf (fourth, "%d %lf\n", num_elements, test_result);
    }

    fclose (first);
    fclose (second);
    fclose (third);
    fclose (fourth);
    
    return 0;
}

double test1 (int num_elements)
{
    double average_time = 0;
    
    for (int num_test = 0; num_test < 3; num_test++)
    {
        struct Stack *stack_ptr = stack_ctr (sizeof (int));

        double cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            push (stack_ptr, &i);
        }

        while (stack_ptr->employment >= num_elements / 10)
        {
            int half = stack_ptr->employment / 2;
            int quarter = stack_ptr->employment / 4;
            for (int i = 0; i < half; i++)
            {
                pop (stack_ptr);
            }
            for (int i = 0; i < quarter; i++)
            {
                push (stack_ptr, &i);
            }
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;
        stack_dtr (stack_ptr);
    }
    average_time /= 3;

    return (average_time / CLOCKS_PER_SEC);
}

double test2 (int num_elements)
{
    double average_time = 0;
    double average_test_1_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        struct Stack *stack_ptr = stack_ctr (sizeof (int));

        double cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            push (stack_ptr, &i);

        }

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                pop (stack_ptr);
            }
        }
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                push (stack_ptr, &j);
            }
        }

        cur_time = cur_time - clock ();

        average_test_1_time += test1 (num_elements);

        cur_time += clock ();

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                pop (stack_ptr);
            }
        }

        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < num_elements / 100; k++)
            {
                push (stack_ptr, &j);
            }
        }
        
        cur_time = clock () - cur_time;
        average_time += cur_time;
        stack_dtr (stack_ptr);
    }
    average_time /= 3;
    average_test_1_time /= 3;

    return (average_time / CLOCKS_PER_SEC) + average_test_1_time;
}

double test3 (int num_elements)
{
    int random_value = 0;
    double average_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        struct Stack *stack_ptr = stack_ctr (sizeof (int));

        for (int i = 0; i <= num_elements; i++)
        {
            push (stack_ptr, &i);
        }

        double cur_time = clock ();

        for (int i = 0; i < num_elements; i++)
        {
            random_value = rand ();
            if (random_value > (RAND_MAX / 2))
            {
                pop (stack_ptr);
            }
            else
            {
                push (stack_ptr, &random_value);
            }
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;
        
        stack_dtr (stack_ptr);
    }
    average_time /= 3;
    
    return (average_time / CLOCKS_PER_SEC);
}

double test4 (int num_elements)
{
    double average_time = 0;

    for (int num_test = 0; num_test < 3; num_test++)
    {
        struct Stack *stack_ptr = stack_ctr (sizeof (int));
        
        double cur_time = clock ();

        for (int i = 0; i <= num_elements; i++)
        {
            push (stack_ptr, &i);
        }

        cur_time = clock () - cur_time;
        average_time += cur_time;

        stack_dtr (stack_ptr);
    }

    average_time /= 3;

    return (average_time / CLOCKS_PER_SEC);
    
}