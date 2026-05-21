#include "arr_stack.h"

void *arr_stack_ctr (size_t size, size_t element_size)
{
    arr_stack_t *stack_ptr = (arr_stack_t *) calloc (1, sizeof (arr_stack_t));
    if (!stack_ptr) return NULL;

    stack_ptr->array = (void *) calloc (size, element_size);
    if (stack_ptr->array == NULL)
    {
        free (stack_ptr);
        return NULL;
    }

    stack_ptr->element_size = element_size;
    stack_ptr->capacity = size;
    stack_ptr->count = 0;

    return stack_ptr;
}

void *arr_stack_dtr (void *stack_ptr)
{
    if (!stack_ptr) return NULL;
    arr_stack_t *stack = stack_ptr;
    free (stack->array);
    free (stack);
    return NULL;
}

status_t arr_push (void *stack_ptr, void *buffer)
{
    if (!stack_ptr) return STATUS_ERR;
    if (!buffer)    return STATUS_ERR;

    arr_stack_t *stack = stack_ptr;

    if (stack->count != stack->capacity - 1)
    {
        memcpy (stack->array + stack->element_size * stack->count, buffer, stack->element_size);
        stack->count++;
        return STATUS_OK;
    }
    
    status_t status = arr_expansion (stack);
    if (status == STATUS_ERR) return STATUS_ERR;

    memcpy (stack->array + stack->element_size * stack->count, buffer, stack->element_size);
    stack->count++;

    return STATUS_OK;
}

status_t arr_expansion (void *stack_ptr)
{
    if (!stack_ptr) return STATUS_OK;
    arr_stack_t *stack = stack_ptr;

    size_t new_size = stack->capacity * EXPANSION_KOEFF;

    void *array_pointer = realloc (stack->array, new_size * stack->element_size);
    if (array_pointer == NULL)
    {
        return STATUS_ERR;
    }

    stack->array = array_pointer;
    stack->capacity = new_size;
    return STATUS_OK;
}

status_t arr_top (void *stack_ptr, void *buffer)
{
    if (!stack_ptr) return STATUS_ERR;
    if (!buffer)    return STATUS_ERR;

    arr_stack_t *stack = stack_ptr;

    if (stack->count == 0)
    {
        return STATUS_ERR;
    }

    memcpy (buffer, stack->array + (stack->count - 1)* stack->element_size, stack->element_size);
    
    return STATUS_OK;
}

status_t arr_pop (void *stack_ptr)
{
    if (!stack_ptr) return STATUS_ERR;

    arr_stack_t *stack = stack_ptr;

    if (stack->count == 0)
    {
        return STATUS_ERR;
    }

    stack->count--;

    if (stack->count > 0 && 
        stack->count <= stack->capacity / NARROWING_KOEFF && 
        stack->capacity > NARROWING_KOEFF) 
    {
        return arr_narrowing (stack);
    }

    return STATUS_OK;
}

status_t arr_narrowing (void *stack_ptr)
{
    if (!stack_ptr) return STATUS_ERR;

    arr_stack_t *stack = stack_ptr;

    size_t new_size = stack->capacity / 2;
    void *new_arr = realloc (stack->array, new_size * stack->element_size);
    
    if (new_arr)
    {
        stack->array = new_arr;
        stack->capacity = new_size;
        return STATUS_OK;
    }
    return STATUS_ERR;
}

int arr_get_count (void *stack_ptr)
{
    if (!stack_ptr) return -1;
    return ((int) (((arr_stack_t *) stack_ptr)->count));
}

void *arr_stack_ctr_for_tests (size_t element_size)
{
    return arr_stack_ctr (1, element_size);
}