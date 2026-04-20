#include "arr_stack.h"

void *arr_stack_ctr (size_t size, size_t element_size)
{
    struct arr_stack *stack_ptr = (struct arr_stack *) calloc (1, sizeof (struct arr_stack));
    if (!stack_ptr) return NULL;

    stack_ptr->array = (void *) calloc (size, element_size);
    if (stack_ptr->array == NULL)
    {
        free (stack_ptr);
        return NULL;
    }
    stack_ptr->element_size = element_size;
    stack_ptr->capacity = size;
    stack_ptr->employment = 0;
    return stack_ptr;
}

void *arr_stack_dtr (void *stack_ptr)
{
    if (!stack_ptr) return NULL;
    struct arr_stack *stack = stack_ptr;
    free (stack->array);
    free (stack);
    return NULL;
}

int arr_push (void *stack_ptr, void *buffer)
{
    if (!stack_ptr) return 0;
    if (!buffer) return 0;
    struct arr_stack *stack = stack_ptr;
    if (stack->employment != stack->capacity - 1)
    {
        memcpy (stack->array + stack->element_size * stack->employment, buffer, stack->element_size);
        stack->employment++;
        return 1;
    }
    else
    {
        size_t new_size = stack->capacity * 2;
        int *array_pointer = realloc (stack->array, new_size * stack->element_size);
        if (array_pointer == NULL)
        {
            return 0;
        }
        stack->array = array_pointer;
        stack->capacity = new_size;
        memcpy (stack->array + stack->element_size * stack->employment, buffer, stack->element_size);
        stack->employment++;
        return 1;
    }
    return 1;
}

int arr_top (void *stack_ptr, void *buffer)
{
    if (!stack_ptr) return 0;
    if (!buffer) return 0;
    struct arr_stack *stack = stack_ptr;

    if (stack->employment == 0)
    {
        return 0;
    }
    else
    {
        memcpy (buffer, stack->array + (stack->employment - 1)* stack->element_size, stack->element_size);
        return 1;
    }
}

int arr_pop (void *stack_ptr)
{
    if (!stack_ptr) return 0;
    struct arr_stack *stack = stack_ptr;

    if (stack->employment == 0)
    {
        return 0;
    }

    stack->employment--;

    if (stack->employment > 0 && 
        stack->employment <= stack->capacity / 4 && 
        stack->capacity > 4) 
    {
        size_t new_size = stack->capacity / 2;
        void *new_arr = realloc (stack->array, new_size * stack->element_size);
        
        if (new_arr)
        {
            stack->array = new_arr;
            stack->capacity = new_size;
        }
    }

    return 1;
}

int arr_get_employment (void *stack_ptr)
{
    if (!stack_ptr) return -1;
    return ((int) (((struct arr_stack *) stack_ptr)->employment));
}

void *arr_stack_ctr_for_tests (size_t element_size)
{
    return arr_stack_ctr (1, element_size);
}